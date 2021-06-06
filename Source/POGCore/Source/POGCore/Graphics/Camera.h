#pragma once

#include "POGMaths.h"

#include <memory>

namespace POG::Core
{
	class Camera
	{
	public:
		static std::shared_ptr<Camera> MainCamera;

		Camera();

		void UpdateView(Maths::Vec3 parentPosition, Maths::Quat parentOrientation);
		void AddPitchAndYaw(float pitchAmount, float yawAmount);
		Maths::Quat GetCameraOrientation() const { return cameraOrientation; }

		Maths::Vec3 GetForwardVec() const { return forwardVec; }
		Maths::Vec3 GetUpVec() const { return upVec; }
		Maths::Vec3 GetRightVec() const { return rightVec; }

		void CalculateProjection();

		void SetFov(float newFov);
		void SetAspectRatio(float newAspectRatio);
		void SetNearZ(float newNearZ);
		void SetFarZ(float newFarZ);

		const Maths::Mat4& GetView() const { return view; }
		const Maths::Mat4& GetProjection() const { return projection; }

	private:
		float pitch, yaw;
		Maths::Quat cameraOrientation;

		Maths::Vec3 forwardVec;
		Maths::Vec3 upVec;
		Maths::Vec3 rightVec;

		float fov;
		float aspectRatio;
		float nearZ, farZ;

		Maths::Mat4 view;
		Maths::Mat4 projection;
	};
}

