#include "POGCorePCH.h"
#include "Systems.h"

#include "POGCore/Graphics/MeshManager.h"
#include "POGCore/Graphics/ShaderManager.h"

namespace POG::Core
{
	Signature CameraUpdateViewSystem::GetSignature(ECSManager& ecsManager)
	{
		Signature signature;
		signature.set(ecsManager.GetComponentTypeId<Transform>());
		signature.set(ecsManager.GetComponentTypeId<AttachedCamera>());
		return signature;
	}

	void CameraUpdateViewSystem::UpdateView()
	{
		for (EntityId entityId : entityIds)
		{
			auto& transform = ecsManager.GetComponent<Transform>(entityId);
			auto& attachedCamera = ecsManager.GetComponent<AttachedCamera>(entityId);

			attachedCamera.camera->UpdateView(transform.position, attachedCamera.relativePosition, transform.orientation, attachedCamera.relativeOrientation);
		}
	}


	Signature MeshRendererSystem::GetSignature(ECSManager& ecsManager)
	{
		Signature signature;
		signature.set(ecsManager.GetComponentTypeId<Transform>());
		signature.set(ecsManager.GetComponentTypeId<MeshRenderer>());
		return signature;
	}

	void MeshRendererSystem::Frame(float alpha)
	{
		for (EntityId entityId : entityIds)
		{
			auto& meshRenderer = ecsManager.GetComponent<MeshRenderer>(entityId);
			auto& transform = ecsManager.GetComponent<Transform>(entityId);

			Graphics::Material& material = *meshRenderer.material;
			material.GetShader().Use();
			material.UpdateShaderUniforms();

			Maths::Vec3 position = Maths::Lerp(transform.prevPosition, transform.position, alpha);
			Maths::Quat orientation = Maths::Lerp(transform.prevOrientation, transform.orientation, alpha);
			Maths::Vec3 scale = Maths::Lerp(transform.prevScale, transform.scale, alpha);
			orientation.w *= -1.0f; // Invert model matrix rotation axes

			Graphics::Shader& shader = material.GetShader();
			shader.SetMatrix4fv("view", 1, false, Maths::ToData(Core::Camera::MainCamera->GetView()));
			shader.SetMatrix4fv("projection", 1, false, Maths::ToData(Core::Camera::MainCamera->GetProjection()));
			shader.SetMatrix4fv("model", 1, false, Maths::ToData(Maths::ToModelMatrix(position, orientation, scale)));

			meshRenderer.mesh->Render();
		}
	}

	Signature PhysicsSystem::GetSignature(ECSManager& ecsManager)
	{
		Signature signature;
		signature.set(ecsManager.GetComponentTypeId<Transform>());
		signature.set(ecsManager.GetComponentTypeId<RigidBody>());
		return signature;
	}

	void PhysicsSystem::Update(float dt)
	{
		for (EntityId entityId : entityIds)
		{
			auto& transform = ecsManager.GetComponent<Transform>(entityId);
			auto& rigidBody = ecsManager.GetComponent<RigidBody>(entityId);

			Maths::Vec3 drag = rigidBody.dragCoef * Maths::Vec3MultiplyPreserveSigns(rigidBody.velocity, rigidBody.velocity);
			Maths::Vec3 acceleration = (rigidBody.force - drag) / rigidBody.mass;

			rigidBody.velocity += acceleration * dt;
			rigidBody.velocity.y = abs(rigidBody.velocity.y) > 0.001f ? rigidBody.velocity.y : 0.0f;
			rigidBody.velocity.z = abs(rigidBody.velocity.z) > 0.001f ? rigidBody.velocity.z : 0.0f;
			rigidBody.velocity.x = abs(rigidBody.velocity.x) > 0.001f ? rigidBody.velocity.x : 0.0f;

			transform.position += rigidBody.velocity * dt;
		}
	}

	Signature SpriteRectColliderRendererSystem::GetSignature(ECSManager& ecsManager)
	{
		Signature signature;
		signature.set(ecsManager.GetComponentTypeId<RectCollider>());
		signature.set(ecsManager.GetComponentTypeId<Sprite>());
		signature.set(ecsManager.GetComponentTypeId<Transform>());
		return signature;
	}

	void SpriteRectColliderRendererSystem::Frame(float alpha)
	{
		Graphics::PolygonMode prevModeFront = Graphics::GetPolygonMode(Graphics::PolygonFace::Front);
		Graphics::PolygonMode prevModeBack = Graphics::GetPolygonMode(Graphics::PolygonFace::Back);

		Graphics::SetPolygonMode(Graphics::PolygonFace::FrontAndBack, Graphics::PolygonMode::Line);

		Graphics::Mesh& mesh = MeshManager::GetDefaultMesh("Square Mesh");

		for (EntityId entityId : entityIds)
		{
			auto& rectCollider = ecsManager.GetComponent<RectCollider>(entityId);
			auto& sprite = ecsManager.GetComponent<Sprite>(entityId);
			auto& transform = ecsManager.GetComponent<Transform>(entityId);

			float ratioX = sprite.texture->GetWidth() / sprite.pixelsToUnitsRatio;
			float ratioY = sprite.texture->GetHeight() / sprite.pixelsToUnitsRatio;

			Maths::Vec3 prevScale = transform.prevScale * Maths::Vec3(ratioX, ratioY, 1.0f);
			Maths::Vec3 currentScale = transform.scale * Maths::Vec3(ratioX, ratioY, 1.0f);

			Maths::Vec3 position = Maths::Lerp(transform.prevPosition, transform.position, alpha);
			Maths::Quat orientation = Maths::Lerp(transform.prevOrientation, transform.orientation, alpha);
			Maths::Vec3 scale = Maths::Lerp(prevScale, currentScale, alpha);

			Graphics::Shader& shader = ShaderManager::GetDefaultShader("Wireframe Shader");
			shader.Use();
			shader.SetMatrix4fv("view", 1, false, Maths::ToData(Core::Camera::MainCamera->GetView()));
			shader.SetMatrix4fv("projection", 1, false, Maths::ToData(Core::Camera::MainCamera->GetProjection()));
			shader.SetMatrix4fv("model", 1, false, Maths::ToData(Maths::ToModelMatrix(position, orientation, scale)));

			mesh.Render();
		}

		Graphics::SetPolygonMode(Graphics::PolygonFace::Front, prevModeFront);
		Graphics::SetPolygonMode(Graphics::PolygonFace::Back, prevModeBack);
	}

	Signature SpriteRendererSystem::GetSignature(ECSManager& ecsManager)
	{
		Signature signature;
		signature.set(ecsManager.GetComponentTypeId<Sprite>());
		signature.set(ecsManager.GetComponentTypeId<Transform>());
		return signature;
	}

	void SpriteRendererSystem::Frame(float alpha)
	{
		Graphics::Mesh& mesh = MeshManager::GetDefaultMesh("Sprite Mesh");

		for (EntityId entityId : entityIds)
		{
			auto& sprite = ecsManager.GetComponent<Sprite>(entityId);
			auto& transform = ecsManager.GetComponent<Transform>(entityId);

			float ratioX = sprite.texture->GetWidth() / sprite.pixelsToUnitsRatio;
			float ratioY = sprite.texture->GetHeight() / sprite.pixelsToUnitsRatio;

			Maths::Vec3 prevScale = transform.prevScale * Maths::Vec3(ratioX, ratioY, 1.0f);
			Maths::Vec3 currentScale = transform.scale * Maths::Vec3(ratioX, ratioY, 1.0f);

			Maths::Vec3 position = Maths::Lerp(transform.prevPosition, transform.position, alpha);
			Maths::Quat orientation = Maths::Lerp(transform.prevOrientation, transform.orientation, alpha);
			Maths::Vec3 scale = Maths::Lerp(prevScale, currentScale, alpha);
			
			sprite.texture->Bind();

			Graphics::Shader& shader = ShaderManager::GetDefaultShader("Sprite Shader");
			shader.Use();
			shader.SetMatrix4fv("view", 1, false, Maths::ToData(Core::Camera::MainCamera->GetView()));
			shader.SetMatrix4fv("projection", 1, false, Maths::ToData(Core::Camera::MainCamera->GetProjection()));
			shader.SetMatrix4fv("model", 1, false, Maths::ToData(Maths::ToModelMatrix(position, orientation, scale)));

			mesh.Render();
		}
	}

	Signature TransformSystem::GetSignature(ECSManager& ecsManager)
	{
		Signature signature;
		signature.set(ecsManager.GetComponentTypeId<Transform>());
		return signature;
	}

	void TransformSystem::Update(float dt)
	{
		for (EntityId entityId : entityIds)
		{
			Transform& transform = ecsManager.GetComponent<Transform>(entityId);
			transform.prevPosition = transform.position;
			transform.prevOrientation = transform.orientation;
			transform.prevScale = transform.scale;
		}
	}
}