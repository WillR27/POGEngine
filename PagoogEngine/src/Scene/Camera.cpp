#include "pgepch.h"
#include "Camera.h"

namespace PEngine
{
	Shared<Camera> Camera::MainCamera = MakeShared<Camera>();

	Camera::Camera()
		: pitch(0.0f)
		, yaw(0.0f)
		, forwardVec(0.0f, 0.0f, 1.0f)
		, upVec(0.0f, 1.0f, 0.0f)
		, rightVec(1.0f, 0.0f, 0.0f)
		, fov(Maths::ToRadians(60.0f))
		, aspectRatio(800.0f / 600.0f)
		, nearZ(0.1f)
		, farZ(100.0f)
		, view()
		, projection(glm::perspective(fov, aspectRatio, nearZ, farZ))
	{
		CalculateProjection();
	}

	void Camera::UpdateView(Vec3 parentPosition, Quat parentOrientation)
	{
		Quat cameraOrientation = Quat(Vec3(pitch, yaw, 0.0f));

		forwardVec = Maths::ToForwardVec(parentOrientation * cameraOrientation);
		upVec = Maths::ToUpVec(parentOrientation * cameraOrientation);
		rightVec = Maths::ToRightVec(parentOrientation * cameraOrientation);

		view = glm::lookAt(parentPosition, parentPosition + forwardVec, upVec);
	}

	void Camera::AddPitchAndYaw(float pitchAmount, float yawAmount)
	{
		pitch -= pitchAmount;
		yaw -= yawAmount;
	}

	void Camera::CalculateProjection()
	{
		projection = glm::perspective(fov, aspectRatio, nearZ, farZ);
		projection[0].x *= -1;
		projection[1].x *= -1;
		projection[2].x *= -1;
		projection[3].x *= -1;
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