#include "pgepch.h"
#include "CameraNew.h"

#include "ECS/Component/Components.h"

namespace PEngine
{
	Shared<CameraNew> CameraNew::MainCamera = MakeShared<CameraNew>();

	CameraNew::CameraNew()
		: pitch(0.0f)
		, yaw(0.0f)
		, forwardVec(0.0f, 0.0f, -1.0f)
		, upVec(0.0f, 1.0f, 0.0f)
		, rightVec(1.0f, 0.0f, 0.0f)
		, fov(Maths::ToRadians(60.0f))
		, aspectRatio(800.0f / 600.0f)
		, nearZ(0.1f)
		, farZ(100.0f)
		, view()
		, projection(glm::perspective(fov, aspectRatio, nearZ, farZ))
	{
	}

	void CameraNew::UpdateView(Vec3 parentPosition, Quat parentOrientation)
	{
		Quat cameraOrientation = Quat(Vec3(pitch, yaw, 0.0f));

		forwardVec = Maths::ToForwardVec(parentOrientation * cameraOrientation);
		upVec = Maths::ToUpVec(parentOrientation * cameraOrientation);
		rightVec = Maths::ToRightVec(parentOrientation * cameraOrientation);

		view = glm::lookAt(parentPosition, parentPosition + forwardVec, upVec);
	}

	void CameraNew::AddPitchAndYaw(float pitchAmount, float yawAmount)
	{
		pitch += pitchAmount;
		yaw += yawAmount;
	}

	Vec3 CameraNew::GetForwardVec() const
	{
		return forwardVec;
	}

	Vec3 CameraNew::GetUpVec() const
	{
		return upVec;
	}

	Vec3 CameraNew::GetRightVec() const
	{
		return rightVec;
	}

	void CameraNew::SetFov(float newFov)
	{
		fov = newFov;
		projection = glm::perspective(fov, aspectRatio, nearZ, farZ);
	}

	void CameraNew::SetAspectRatio(float newAspectRatio)
	{
		aspectRatio = newAspectRatio;
		projection = glm::perspective(fov, aspectRatio, nearZ, farZ);
	}

	void CameraNew::SetNearZ(float newNearZ)
	{
		nearZ = newNearZ;
		projection = glm::perspective(fov, aspectRatio, nearZ, farZ);
	}

	void CameraNew::SetFarZ(float newFarZ)
	{
		farZ = newFarZ;
		projection = glm::perspective(fov, aspectRatio, nearZ, farZ);
	}

	const Mat4& CameraNew::GetView() const
	{
		return view;
	}

	const Mat4& CameraNew::GetProjection() const
	{
		return projection;
	}
}