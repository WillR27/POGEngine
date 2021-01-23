#include "pgepch.h"
#include "Layer.h"

#include "Scene/Camera.h"
#include "Util/Timer.h"

namespace PEngine
{
	Layer::Layer(const char* name)
		: name(name)
		, inputManager()
		, ecsManager()
	{
	}

	Layer::~Layer()
	{

	}

	void Layer::PreInit()
	{
		ecsManager.Init();

		ecsManager.RegisterComponent<ECSTransform>();
		ecsManager.RegisterComponent<ECSRigidBody>();
		ecsManager.RegisterComponent<ECSBoxCollider>();
		ecsManager.RegisterComponent<ECSMeshRenderer>();
		ecsManager.RegisterComponent<ECSCamera>();

		transformSystem = ecsManager.RegisterSystem<TransformSystem>();
		physicsSystem = ecsManager.RegisterSystem<PhysicsSystem>();
		collisionsSystem = ecsManager.RegisterSystem<CollisionsSystem>();
		meshRendererSystem = ecsManager.RegisterSystem<MeshRendererSystem>();
		cameraUpdateViewSystem = ecsManager.RegisterSystem<CameraUpdateViewSystem>();
		rayCastSystem = ecsManager.RegisterSystem<RayCastSystem>();
	}

	void Layer::Init()
	{
	}

	void Layer::PostInit()
	{
	}

	void Layer::PreInputUpdate(float dt)
	{
	}

	void Layer::InputUpdate(float dt)
	{
		inputManager.Send(dt);
	}

	void Layer::PostInputUpdate(float dt)
	{
	}

	void Layer::PreUpdate(float dt)
	{
	}

	void Layer::Update(float dt)
	{
		physicsSystem->Update(dt);
	}

	void Layer::PostUpdate(float dt)
	{
	}

	void Layer::CollisionsPreUpdate(float dt)
	{
	}

	void Layer::CollisionsUpdate(float dt)
	{
		collisionsSystem->Update(dt);
	}

	void Layer::CollisionsPostUpdate(float dt)
	{
		transformSystem->Update(dt);
		cameraUpdateViewSystem->UpdateView();
	}

	void Layer::PreFrameUpdate(float alpha)
	{
	}

	void Layer::FrameUpdate(float alpha)
	{
		meshRendererSystem->FrameUpdate(alpha);
	}

	void Layer::PostFrameUpdate(float alpha)
	{
	}

	void Layer::PreHandleEvent(Event& e)
	{
		EventDispatcher ed(e);
		ed.Dispatch<KeyEvent>(PG_BIND_FN(inputManager.HandleKeyEvent));
		ed.Dispatch<MouseMoveEvent>(PG_BIND_FN(inputManager.HandleMouseMoveEvent));
		ed.Dispatch<MouseButtonEvent>(PG_BIND_FN(inputManager.HandleMouseButtonEvent));

		if (!e.IsHandled())
		{
			this->HandleEvent(e);
		}
	}

	void Layer::HandleEvent(Event& e)
	{
	}

	void Layer::PostHandleEvent(Event& e)
	{
	}

	void TransformSystem::Update(float dt)
	{
		//PG_SCOPED_PROFILE("Transform");
		for (EntityId entityId : entityIds)
		{
			auto& transform = ecsManager.GetComponent<ECSTransform>(entityId);
			transform.prevPosition = transform.position;
			transform.prevOrientation = transform.orientation;
			transform.prevScale = transform.scale;
		}
	}

	void PhysicsSystem::Update(float dt)
	{
		//PG_SCOPED_PROFILE("Physics");
		for (EntityId entityId : entityIds)
		{
			auto& transform = ecsManager.GetComponent<ECSTransform>(entityId);
			auto& rigidBody = ecsManager.GetComponent<ECSRigidBody>(entityId);
			
			Vec3 drag = rigidBody.dragCoef * Maths::Vec3MultiplyPreserveSigns(rigidBody.velocity, rigidBody.velocity);
			Vec3 acceleration = (rigidBody.force - drag) / rigidBody.mass;

			rigidBody.velocity += acceleration * dt;
			rigidBody.velocity.y = abs(rigidBody.velocity.y) > 0.001f ? rigidBody.velocity.y : 0.0f;
			rigidBody.velocity.z = abs(rigidBody.velocity.z) > 0.001f ? rigidBody.velocity.z : 0.0f;
			rigidBody.velocity.x = abs(rigidBody.velocity.x) > 0.001f ? rigidBody.velocity.x : 0.0f;

			transform.position += rigidBody.velocity * dt;
		}
	}

	void CollisionsSystem::Update(float dt)
	{
		//PG_SCOPED_PROFILE("Collision");
		// (n^2 + n) / 2 checks
		for (auto& it1 = entityIds.begin(); it1 != entityIds.end(); it1++)
		{
			EntityId entityId1 = *it1;

			auto& boxCollider1 = ecsManager.GetComponent<ECSBoxCollider>(entityId1);
			auto& transform1 = ecsManager.GetComponent<ECSTransform>(entityId1);
			auto& rigidBody1 = ecsManager.GetComponent<ECSRigidBody>(entityId1);

			AABB<3>& aabb1 = boxCollider1.aabb.CreateTransformedAABB(transform1.position);

			for (auto& it2 = std::next(it1, 1); it2 != entityIds.end(); it2++)
			{
				EntityId entityId2 = *it2;

				auto& boxCollider2 = ecsManager.GetComponent<ECSBoxCollider>(entityId2);
				auto& transform2 = ecsManager.GetComponent<ECSTransform>(entityId2);
				auto& rigidBody2 = ecsManager.GetComponent<ECSRigidBody>(entityId2);

				//PG_START_SCOPED_PROFILE("Collisions ECS");
				AABB<3>& aabb2 = boxCollider2.aabb.CreateTransformedAABB(transform2.position);

				Shared<Hit> hit = aabb1.IsCollidingWith2(aabb2);

				if (hit)
				{
					transform1.position += -hit->overlap;

					Vec3 position1 = transform1.position;
					Vec3 position2 = transform2.position;

					Vec3 velocity1 = rigidBody1.velocity;
					Vec3 velocity2 = rigidBody2.velocity;

					float mass1 = rigidBody1.mass;
					float mass2 = rigidBody2.mass;

					// This gives us the direction of the collision from 1 to 2
					//Vec3 collisionDirection = Maths::Normalise(position2 - position1);
					Vec3 collisionDirection = hit->surfaceNormal;

					// This gives us the relative velocity from 2 to 1
					Vec3 relativeVelocity = velocity1 - velocity2;

					// The speed of the collision is the dot product between the collision direction and the relative velocity
					float speedOfCollision = Maths::DotProduct(collisionDirection, relativeVelocity);

					float coefficientOfRestitution = (2.0f - (boxCollider1.stickiness + boxCollider2.stickiness)) / 2.0f;
					float speedAfterCollision = coefficientOfRestitution * speedOfCollision;

					if (speedAfterCollision <= 0.0f)
					{
						continue;
					}

					float impulse = speedAfterCollision / (mass1 + mass2);
					Vec3 changeInVelocity1 = -impulse * mass1 * collisionDirection;
					Vec3 changeInVelocity2 = impulse * mass1 * collisionDirection;

					rigidBody1.velocity += changeInVelocity1;
					rigidBody2.velocity += changeInVelocity2;
				}
				//PG_END_SCOPED_PROFILE();
			}
		}
	}

	void MeshRendererSystem::FrameUpdate(float alpha)
	{
		//PG_SCOPED_PROFILE("Render");
		for (EntityId entityId : entityIds)
		{
			auto& meshRenderer = ecsManager.GetComponent<ECSMeshRenderer>(entityId);
			auto& transform = ecsManager.GetComponent<ECSTransform>(entityId);

			Mesh* mesh = meshRenderer.mesh;
			Material* material = meshRenderer.material;

			if (mesh != nullptr)
			{
				material->GetShader().Use();
				material->UpdateShaderUniforms();

				Vec3 position = Maths::Lerp(transform.prevPosition, transform.position, alpha);
				Quat orientation = Maths::Lerp(transform.prevOrientation, transform.orientation, alpha); // TODO: Fix flickering
				Vec3 scale = Maths::Lerp(transform.prevScale, transform.scale, alpha);

				Shader& shader = material->GetShader();
				shader.SetMatrix4fv("view", 1, false, Camera::MainCamera->GetView());
				shader.SetMatrix4fv("projection", 1, false, Camera::MainCamera->GetProjection());
				shader.SetMatrix4fv("model", 1, false, Maths::ToModelMatrix(position, orientation, scale));

				mesh->Render();
			}
		}
	}

	void CameraUpdateViewSystem::UpdateView()
	{
		for (EntityId entityId : entityIds)
		{
			auto& transform = ecsManager.GetComponent<ECSTransform>(entityId);
			auto& camera = ecsManager.GetComponent<ECSCamera>(entityId);

			camera.camera->UpdateView(transform.position, transform.orientation);
		}
	}

	RayCastResult RayCastSystem::RayCast(Vec3 position, Vec3 direction, EntityId entityIdToIgnore)
	{
		const float step = 0.1f;
		const float limit = 100.0f;

		RayCastResult rayCastResult;
		float totalDistance = 0.0f;

		Vec3 newPosition = position;

		while (totalDistance < limit && rayCastResult.entityId == 0)
		{
			newPosition += direction * step;
			totalDistance += step;

			for (EntityId entityId : entityIds)
			{
				if (entityId == entityIdToIgnore)
				{
					continue;
				}

				auto& transform = ecsManager.GetComponent<ECSTransform>(entityId);
				auto& boxCollider = ecsManager.GetComponent<ECSBoxCollider>(entityId);

				if (boxCollider.aabb.CreateTransformedAABB(transform.position).IsCollidingWith(newPosition))
				{
					rayCastResult.hit = true;
					rayCastResult.entityId = entityId;
					break;
				}
			}
		}

		return rayCastResult;
	}
}