#include "pgepch.h"
#include "Camera.h"

namespace PEngine
{
	// Assigned to a default camera by default
	Shared<Camera> Camera::MainCamera = MakeShared<Camera>();

	Camera::Camera(Vec3 cameraPos, Vec3 cameraTarget, Vec3 cameraDirection)
		: worldUp(Vec3(0.0f, 1.0f, 0.0f))
		, cameraPos(cameraPos)
		, cameraTarget(cameraTarget)
		, cameraForward(cameraDirection)
		, cameraRight(-glm::normalize(glm::cross(worldUp, cameraDirection)))
		, cameraUp(glm::cross(cameraDirection, cameraRight))
		, view(glm::lookAt(cameraPos, cameraTarget, worldUp))
		, fov(glm::radians(60.0f))
		, aspectRatio(800.0f / 600.0f)
		, nearZ(0.1f)
		, farZ(100.0f)
		, projection(glm::perspective(fov, aspectRatio, nearZ, farZ))
		//, projection(glm::ortho(0.0f, 5.0f, 0.0f, 4.0f, nearZ, farZ))
	{
	}

	Camera::~Camera()
	{
	}

	const Mat4& Camera::GetView() const
	{
		return view;
	}

	const Mat4& Camera::GetProjection() const
	{
		return projection;
	}

	void Camera::SetCameraPos(Vec3 newCameraPos)
	{
		cameraPos = newCameraPos;
		cameraForward = glm::normalize(cameraPos - cameraTarget);
		cameraRight = -glm::normalize(glm::cross(worldUp, cameraForward));
		cameraUp = glm::cross(cameraForward, cameraRight);
		view = glm::lookAt(cameraPos, cameraTarget, worldUp);
	}

	void Camera::SetCameraTarget(Vec3 newCameraTarget)
	{
		cameraTarget = newCameraTarget;
		cameraForward = glm::normalize(cameraPos - cameraTarget);
		cameraRight = -glm::normalize(glm::cross(worldUp, cameraForward));
		cameraUp = glm::cross(cameraForward, cameraRight);
		view = glm::lookAt(cameraPos, cameraTarget, worldUp);
	}

	void Camera::SetCameraDirection(Vec3 newCameraDirection)
	{
		cameraForward = newCameraDirection;
		cameraRight = -glm::normalize(glm::cross(worldUp, cameraForward));
		cameraUp = glm::cross(cameraForward, cameraRight);
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
}