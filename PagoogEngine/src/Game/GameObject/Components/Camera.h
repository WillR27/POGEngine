#pragma once

#include "Maths/Maths.h"
#include "Game/GameObject/Components/Component.h"

namespace PEngine
{
	class Camera : public _Component
	{
	public:
		static Camera* MainCamera;

		Camera();
		virtual ~Camera() override = default;

		virtual _Component* Clone() const override;

		void Update(float dt);

		void AddPitchAndYaw(float pitchAmount, float yawAmount);

		Vec3 GetForwardVec() const;
		Vec3 GetUpVec() const;
		Vec3 GetRightVec() const;

		void SetFov(float newFov);
		void SetAspectRatio(float newAspectRatio);
		void SetNearZ(float newNearZ);
		void SetFarZ(float newFarZ);

		const Mat4& GetView() const;
		const Mat4& GetProjection() const;

		static constexpr const char* ComponentName()
		{
			return STRINGIFY(Camera);
		}

		virtual std::string GetComponentName() const override;

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

