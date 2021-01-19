#include "pgepch.h"
#include "Layer.h"

#include "Game/GameObject/GameObject.h"
#include "Util/Timer.h"

#include "Scene/CameraNew.h"

namespace PEngine
{
	Layer* Layer::ActiveLayer = nullptr;

	Layer::Layer(const char* name)
		: name(name)
		, inputManager()
		, coordinator()
		, gameObjects()
		, boxColliders()
		, cameras()
		, meshRenderers()
		, rigidBodies()
		, transforms()
	{
		// TODO: Move to Init()
		coordinator.Init();

		coordinator.RegisterComponent<ECSTransform>();
		coordinator.RegisterComponent<ECSRigidBody>();
		coordinator.RegisterComponent<ECSBoxCollider>();
		coordinator.RegisterComponent<ECSMeshRenderer>();
		coordinator.RegisterComponent<ECSCamera>();

		transformSystem = coordinator.RegisterSystem<TransformSystem>();
		coordinator.SetSystemSignature<TransformSystem>(TransformSystem::GetSignature(coordinator));

		physicsSystem = coordinator.RegisterSystem<PhysicsSystem>();
		coordinator.SetSystemSignature<PhysicsSystem>(PhysicsSystem::GetSignature(coordinator));

		collisionsSystem = coordinator.RegisterSystem<CollisionsSystem>();
		coordinator.SetSystemSignature<CollisionsSystem>(CollisionsSystem::GetSignature(coordinator));

		meshRendererSystem = coordinator.RegisterSystem<MeshRendererSystem>();
		coordinator.SetSystemSignature<MeshRendererSystem>(MeshRendererSystem::GetSignature(coordinator));

		cameraUpdateViewSystem = coordinator.RegisterSystem<CameraUpdateViewSystem>();
		coordinator.SetSystemSignature<CameraUpdateViewSystem>(CameraUpdateViewSystem::GetSignature(coordinator));
	}

	Layer::~Layer()
	{
		for (GameObject* gameObject : gameObjects)
		{
			delete gameObject;
		}
	}

	void Layer::InputUpdate(float dt)
	{
		for (Transform* transform : transforms)
		{
			if (transform != nullptr)
			{
				transform->PreInputUpdate();
			}
		}

		transformSystem->Update(dt, coordinator);

		inputManager.Send(dt);
	}

	void Layer::PreUpdate(float dt)
	{
		for (GameObject* gameObject : gameObjects)
		{
			gameObject->Update(dt);
		}
	}

	void Layer::PostUpdate(float dt)
	{
		for (RigidBody* rigidBody : rigidBodies)
		{
			if (rigidBody != nullptr)
			{
				rigidBody->Update(dt);
			}
		}

		physicsSystem->Update(dt, coordinator);

		for (Camera* camera : cameras)
		{
			if (camera != nullptr)
			{
				camera->Update(dt);
			}
		}
	}

	void Layer::CollisionsPreUpdate(float dt)
	{
	}

	void Layer::CollisionsPostUpdate(float dt)
	{
		if (boxColliders.size() > 1)
		{
			for (int i = 0; i < boxColliders.size(); i++)
			{
				for (int j = i + 1; j < boxColliders.size(); j++)
				{
					if (boxColliders[i] != nullptr && boxColliders[j] != nullptr)
					{
						boxColliders[i]->CollideWith(*boxColliders[j]);
					}
				}
			}
		}

		collisionsSystem->Update(dt, coordinator);

		cameraUpdateViewSystem->UpdateView(coordinator);
	}

	void Layer::PreFrameUpdate(float alpha)
	{
		for (GameObject* gameObject : gameObjects)
		{
			gameObject->FrameUpdate(alpha);
		}
	}

	void Layer::PostFrameUpdate(float alpha)
	{
		for (MeshRenderer* meshRenderer : meshRenderers)
		{
			if (meshRenderer != nullptr)
			{
				meshRenderer->FrameUpdate(alpha);
			}
		}

		meshRendererSystem->FrameUpdate(alpha, coordinator);
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

	const char* Layer::GetName() const
	{
		return name;
	}

	void TransformSystem::Update(float dt, ECSCoordinator& coordinator)
	{
		//PG_SCOPED_PROFILE("Transform");
		for (const auto& entity : entities)
		{
			ECSTransform& transform = coordinator.GetComponent<ECSTransform>(entity);
			transform.prevPosition = transform.position;
			transform.prevOrientation = transform.orientation;
			transform.prevScale = transform.scale;
		}
	}

	void PhysicsSystem::Update(float dt, ECSCoordinator& coordinator)
	{
		//PG_SCOPED_PROFILE("Physics");
		for (const auto& entity : entities)
		{
			ECSTransform& transform = coordinator.GetComponent<ECSTransform>(entity);
			ECSRigidBody& rigidBody = coordinator.GetComponent<ECSRigidBody>(entity);

			Vec3 drag = rigidBody.dragCoef * Maths::Vec3MultiplyPreserveSigns(rigidBody.velocity, rigidBody.velocity);
			Vec3 acceleration = (rigidBody.force - drag) / rigidBody.mass;

			rigidBody.velocity += acceleration * dt;
			rigidBody.velocity.y = abs(rigidBody.velocity.y) > 0.001f ? rigidBody.velocity.y : 0.0f;
			rigidBody.velocity.z = abs(rigidBody.velocity.z) > 0.001f ? rigidBody.velocity.z : 0.0f;
			rigidBody.velocity.x = abs(rigidBody.velocity.x) > 0.001f ? rigidBody.velocity.x : 0.0f;

			transform.position += rigidBody.velocity * dt;
		}
	}

	void CollisionsSystem::Update(float dt, ECSCoordinator& coordinator)
	{
		//PG_SCOPED_PROFILE("Collision");
		// (n^2 + n) / 2 checks
		for (auto& it1 = entities.begin(); it1 != entities.end(); it1++)
		{
			for (auto& it2 = std::next(it1, 1); it2 != entities.end(); it2++)
			{
				Entity entity1 = *it1;
				Entity entity2 = *it2;
				
				ECSBoxCollider& boxCollider1 = coordinator.GetComponent<ECSBoxCollider>(entity1);
				ECSBoxCollider& boxCollider2 = coordinator.GetComponent<ECSBoxCollider>(entity2);

				ECSTransform& transform1 = coordinator.GetComponent<ECSTransform>(entity1);
				ECSTransform& transform2 = coordinator.GetComponent<ECSTransform>(entity2);
				
				AABB<3>& aabb1 = boxCollider1.aabb;
				Vec3 min1(transform1.position);
				min1.x -= aabb1.GetRadii()[0];
				min1.y -= aabb1.GetRadii()[1];
				min1.z -= aabb1.GetRadii()[2];
				Vec3 max1(transform1.position);
				max1.x += aabb1.GetRadii()[0];
				max1.y += aabb1.GetRadii()[1];
				max1.z += aabb1.GetRadii()[2];
				aabb1 = AABB<3>(min1, max1);

				AABB<3>& aabb2 = boxCollider2.aabb;
				Vec3 min2(transform2.position);
				min2.x -= aabb2.GetRadii()[0];
				min2.y -= aabb2.GetRadii()[1];
				min2.z -= aabb2.GetRadii()[2];
				Vec3 max2(transform2.position);
				max2.x += aabb2.GetRadii()[0];
				max2.y += aabb2.GetRadii()[1];
				max2.z += aabb2.GetRadii()[2];
				aabb2 = AABB<3>(min2, max2);

				Shared<Hit> hit = aabb1.IsCollidingWith2(aabb2);

				if (hit)
				{
					transform1.position += -hit->overlap;

					ECSRigidBody& rigidBody1 = coordinator.GetComponent<ECSRigidBody>(entity1);
					ECSRigidBody& rigidBody2 = coordinator.GetComponent<ECSRigidBody>(entity2);

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
			}
		}
	}

	void MeshRendererSystem::FrameUpdate(float alpha, ECSCoordinator& coordinator)
	{
		//PG_SCOPED_PROFILE("Render");
		for (const auto& entity : entities)
		{
			ECSMeshRenderer& meshRenderer = coordinator.GetComponent<ECSMeshRenderer>(entity);
			ECSTransform& transform = coordinator.GetComponent<ECSTransform>(entity);

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
				shader.SetMatrix4fv("view", 1, false, CameraNew::MainCamera->GetView());
				shader.SetMatrix4fv("projection", 1, false, CameraNew::MainCamera->GetProjection());
				shader.SetMatrix4fv("model", 1, false, Maths::ToModelMatrix(position, orientation, scale));

				mesh->Render();
			}
		}
	}

	void CameraUpdateViewSystem::UpdateView(ECSCoordinator& coordinator)
	{
		for (const auto& entity : entities)
		{
			auto& transform = coordinator.GetComponent<ECSTransform>(entity);
			auto& camera = coordinator.GetComponent<ECSCamera>(entity);

			camera.camera->UpdateView(transform.position, transform.orientation);
		}
	}
}