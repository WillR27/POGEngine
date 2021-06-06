#include "POGRenderPCH.h"
#include "Camera.h"

namespace POG::Render
{
	std::shared_ptr<Camera> Camera::MainCamera = std::make_shared<Camera>();

	Camera::Camera()
		: pitch(0.0f)
		, yaw(0.0f)
		, cameraOrientation()
		, forwardVec(0.0f, 0.0f, 1.0f)
		, upVec(0.0f, 1.0f, 0.0f)
		, rightVec(1.0f, 0.0f, 0.0f)
		, fov(Maths::ToRadians(90.0f))
		, aspectRatio(1200.0f / 800.0f)
		, nearZ(0.1f)
		, farZ(100.0f)
		, view()
		, projection(glm::perspective(fov, aspectRatio, nearZ, farZ))
	{
		CalculateProjection();
	}

	void Camera::UpdateView(Maths::Vec3 parentPosition, Maths::Quat parentOrientation)
	{
		cameraOrientation = Maths::Quat(Maths::Vec3(pitch, yaw, 0.0f));

		Maths::Quat orientation = Maths::Normalise(parentOrientation * cameraOrientation);
		forwardVec = Maths::ToForwardVec(orientation);
		upVec = Maths::ToUpVec(orientation);
		rightVec = Maths::ToRightVec(orientation);

		view = glm::lookAt(parentPosition, parentPosition + forwardVec, upVec);
	}

	void Camera::AddPitchAndYaw(float pitchAmount, float yawAmount)
	{
		pitch += pitchAmount;
		yaw += yawAmount;
	}

	void Camera::CalculateProjection()
	{
		projection = glm::perspective(fov, aspectRatio, nearZ, farZ);
	}

	void Camera::SetFov(float newFov)
	{
		fov = newFov;
		CalculateProjection();
	}

	void Camera::SetAspectRatio(float newAspectRatio)
	{
		aspectRatio = newAspectRatio;
		CalculateProjection();
	}

	void Camera::SetNearZ(float newNearZ)
	{
		nearZ = newNearZ;
		CalculateProjection();
	}

	void Camera::SetFarZ(float newFarZ)
	{
		farZ = newFarZ;
		CalculateProjection();
	}
}
