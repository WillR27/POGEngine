#include "pgepch.h"
#include "Camera.h"

#include "Game/GameObject/GameObject.h"
#include "Game/GameObject/Components/Components.h"

namespace PEngine
{
	// Assigned to a default camera by default
	Camera* Camera::MainCamera = nullptr; // TODO: Replace access with getter/setter

	Camera::Camera()
		: pitch(0.0f)
		, yaw(0.0f)
		, forwardVec(0.0f, 0.0f, -1.0f)
		, upVec(0.0f, 1.0f, 0.0f)
		, rightVec(1.0f, 0.0f, 0.0f)
		, fov(glm::radians(60.0f))
		, aspectRatio(800.0f / 600.0f)
		, nearZ(0.1f)
		, farZ(100.0f)
		, view()
		, projection(glm::perspective(fov, aspectRatio, nearZ, farZ))
		//, projection(glm::ortho(0.0f, 5.0f, 0.0f, 4.0f, nearZ, farZ))
	{
	}

	_Component* Camera::Clone() const
	{
		return new Camera(*this);
	}

	void Camera::Update(float dt)
	{
		auto transform = gameObject->GetComponent<Transform>();
		Quat cameraOrientation = Quat(Vec3(pitch, yaw, 0.0f));
		
		forwardVec = Maths::ToForwardVec(transform->GetOrientation() * cameraOrientation);
		upVec = Maths::ToUpVec(transform->GetOrientation() * cameraOrientation);
		rightVec = Maths::ToRightVec(transform->GetOrientation() * cameraOrientation);

		view = glm::lookAt(transform->GetPosition(), transform->GetPosition() + forwardVec, upVec);
	}

	void Camera::AddPitchAndYaw(float pitchAmount, float yawAmount)
	{
		pitch += pitchAmount;
		yaw += yawAmount;

		// TOOD: Don't think we need?
		//if (pitch < -Maths::Pi())
		//{
		//	pitch = pitch + Maths::TwoPi();
		//}
		//else if (pitch > Maths::Pi())
		//{
		//	pitch = pitch - Maths::TwoPi();
		//}

		// TOOD: Don't think we need?
		//if (yaw < -Maths::Pi())
		//{
		//	yaw = yaw + Maths::TwoPi();
		//}
		//else if (yaw > Maths::Pi())
		//{
		//	yaw = yaw - Maths::TwoPi();
		//}
	}

	Vec3 Camera::GetForwardVec() const
	{
		return forwardVec;
	}

	Vec3 Camera::GetUpVec() const
	{
		return upVec;
	}

	Vec3 Camera::GetRightVec() const
	{
		return rightVec;
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

	const Mat4& Camera::GetView() const
	{
		return view;
	}

	const Mat4& Camera::GetProjection() const
	{
		return projection;
	}

	std::string Camera::GetComponentName() const
	{
		return ComponentName();
	}
}