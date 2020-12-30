#pragma once

#include "Maths/Maths.h"

namespace PEngine
{
	class Camera
	{
	public:
		static Shared<Camera> MainCamera;

		Camera(Vec3 cameraPos = Vec3(0.0f, 0.0f, 0.0f), Vec3 cameraTarget = Vec3(0.0f, 0.0f, 0.0f), Vec3 cameraDirection = Vec3(0.0f, 0.0f, 1.0f));
		~Camera();

		const Mat4& GetView() const;
		const Mat4& GetProjection() const;

		void SetCameraPos(Vec3 newCameraPos);
		void SetCameraTarget(Vec3 newCameraTarget);
		void SetCameraDirection(Vec3 newCameraDirection);

		void SetFov(float newFov);
		void SetAspectRatio(float newAspectRatio);
		void SetNearZ(float newNearZ);
		void SetFarZ(float newFarZ);

	private:
		Vec3 worldUp;

		Vec3 cameraPos;
		Vec3 cameraTarget;
		Vec3 cameraDirection;

		Vec3 cameraRight;
		Vec3 cameraUp;

		float fov;
		float aspectRatio;
		float nearZ;
		float farZ;

		Mat4 view;
		Mat4 projection;
	};
}

