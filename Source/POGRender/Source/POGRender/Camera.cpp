#include "POGRenderPCH.h"
#include "Camera.h"

namespace POG::Render
{
	std::shared_ptr<Camera> Camera::MainCamera = std::make_shared<Camera>();

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

	void Camera::UpdateView(Maths::Vec3 parentPosition, Maths::Quat parentOrientation)
	{
		Maths::Quat cameraOrientation = Maths::Quat(Maths::Vec3(pitch, yaw, 0.0f));
		//cameraOrientation.w *= -1.0f; // Invert view matrix rotation axes
		parentOrientation.w *= -1.0f; // Invert view matrix rotation axes

		forwardVec = Maths::ToForwardVec(parentOrientation * cameraOrientation);
		upVec = Maths::ToUpVec(parentOrientation * cameraOrientation);
		rightVec = Maths::ToRightVec(parentOrientation * cameraOrientation);

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
		projection[0].x *= -1; // Covert to left handed coordinate system
		projection[1].x *= -1; // Covert to left handed coordinate system
		projection[2].x *= -1; // Covert to left handed coordinate system
		projection[3].x *= -1; // Covert to left handed coordinate system
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
