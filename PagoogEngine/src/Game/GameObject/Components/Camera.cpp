#include "pgepch.h"
#include "Camera.h"

#include "Game/GameObject/GameObject.h"
#include "Game/GameObject/Components/Components.h"

namespace PEngine
{
	// Assigned to a default camera by default
	Camera* Camera::MainCamera = nullptr; // TODO: Replace access with getter/setter

	Camera::Camera()
		: worldUp(Vec3(0.0f, 1.0f, 0.0f))
		, fov(glm::radians(60.0f))
		, aspectRatio(800.0f / 600.0f)
		, nearZ(0.1f)
		, farZ(100.0f)
		, projection(glm::perspective(fov, aspectRatio, nearZ, farZ))
		//, projection(glm::ortho(0.0f, 5.0f, 0.0f, 4.0f, nearZ, farZ))
	{
	}

	Component* Camera::Clone() const
	{
		return new Camera(*this);
	}

	const Mat4 Camera::GetView() const
	{
		Transform* transform = gameObject->GetComponent<Transform>();
		
		return glm::lookAt(transform->GetPosition(), transform->GetPosition() + transform->ToForwardVec(), worldUp);
	}

	const Mat4& Camera::GetProjection() const
	{
		return projection;
	}

	void Camera::SetFov(float newFov)
	{
		fov = newFov;
		projection = glm::perspective(fov, aspectRatio, nearZ, farZ);
	}

	void Camera::SetAspectRatio(float newAspectRatio)
	{
		aspectRatio = newAspectRatio;
		projection = glm::perspective(fov, aspectRatio, nearZ, farZ);
	}

	void Camera::SetNearZ(float newNearZ)
	{
		nearZ = newNearZ;
		projection = glm::perspective(fov, aspectRatio, nearZ, farZ);
	}

	void Camera::SetFarZ(float newFarZ)
	{
		farZ = newFarZ;
		projection = glm::perspective(fov, aspectRatio, nearZ, farZ);
	}

	std::string Camera::GetComponentName() const
	{
		return ComponentName();
	}
}