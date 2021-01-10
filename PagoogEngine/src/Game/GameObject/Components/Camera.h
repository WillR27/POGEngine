#pragma once

#include "Maths/Maths.h"
#include "Game/GameObject/Components/Component.h"

namespace PEngine
{
	class Camera : public Component
	{
	public:
		static Camera* MainCamera;

		Camera();
		virtual ~Camera() override = default;

		virtual Component* Clone() const override;

		const Mat4 GetView() const;
		const Mat4& GetProjection() const;

		void SetCameraTarget(Vec3 newCameraTarget);

		void SetFov(float newFov);
		void SetAspectRatio(float newAspectRatio);
		void SetNearZ(float newNearZ);
		void SetFarZ(float newFarZ);

		static constexpr const char* ComponentName()
		{
			return STRINGIFY(Camera);
		}

		virtual std::string GetComponentName() const override;

	private:
		Vec3 worldUp;

		float fov;
		float aspectRatio;
		float nearZ;
		float farZ;

		Mat4 projection;
	};
}

