#pragma once

#include "Maths/Maths.h"

namespace PEngine
{
	class Camera
	{
	public:
		static Shared<Camera> MainCamera;

		Camera();

		void UpdateView(Vec3 parentPosition, Quat parentOrientation);
		void AddPitchAndYaw(float pitchAmount, float yawAmount);

		Vec3 GetForwardVec() const { return forwardVec; }
		Vec3 GetUpVec() const { return upVec; }
		Vec3 GetRightVec() const { return rightVec; }

		void SetFov(float newFov);
		void SetAspectRatio(float newAspectRatio);
		void SetNearZ(float newNearZ);
		void SetFarZ(float newFarZ);

		const Mat4& GetView() const { return view; }
		const Mat4& GetProjection() const { return projection; }

	private:
		float pitch, yaw;

		Vec3 forwardVec;
		Vec3 upVec;
		Vec3 rightVec;

		float fov;
		float aspectRatio;
		float nearZ, farZ;

		Mat4 view;
		Mat4 projection;
	};
}

