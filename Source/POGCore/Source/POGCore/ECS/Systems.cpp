#include "POGCorePCH.h"
#include "Systems.h"

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
			auto& camera = ecsManager.GetComponent<AttachedCamera>(entityId);

			camera.camera->UpdateView(transform.position, transform.orientation);
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

			Render::Material& material = *meshRenderer.material;
			material.GetShader().Use();
			material.UpdateShaderUniforms();

			Maths::Vec3 position = Maths::Lerp(transform.prevPosition, transform.position, alpha);
			Maths::Quat orientation = Maths::Lerp(transform.prevOrientation, transform.orientation, alpha);
			Maths::Vec3 scale = Maths::Lerp(transform.prevScale, transform.scale, alpha);
			orientation.w *= -1.0f; // Invert model matrix rotation axes

			Render::Shader& shader = material.GetShader();
			shader.SetMatrix4fv("view", 1, false, Maths::ToData(Render::Camera::MainCamera->GetView()));
			shader.SetMatrix4fv("projection", 1, false, Maths::ToData(Render::Camera::MainCamera->GetProjection()));
			shader.SetMatrix4fv("model", 1, false, Maths::ToData(Maths::ToModelMatrix(position, orientation, scale)));

			meshRenderer.mesh->Render();
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