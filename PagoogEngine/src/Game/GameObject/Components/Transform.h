#pragma once

#include "Maths/Maths.h"
#include "Game/GameObject/Components/Component.h"

namespace PEngine
{
	class Transform : public _Component
	{
	public:
		Transform(Vec3 position = Vec3(0.0f, 0.0f, 0.0f), Quat orientation = Quat(Vec3(0.0f, 0.0f, 0.0f)), Vec3 scale = Vec3(1.0f, 1.0f, 1.0f));
		virtual ~Transform() = default;

		virtual _Component* Clone() const override;

		void PreInputUpdate();

		Vec3 GetPosition() const;
		Vec3 GetPrevPosition() const;
		void SetPosition(Vec3 newPosition);
		void Translate(Vec3 translation);

		Quat GetOrientation() const;
		Quat GetPrevOrientation() const;
		void SetOrientation(Vec3 newOrientation);
		void SetOrientation(Quat newOrientation);

		void Rotate(Quat rotation);
		void Rotate(Vec3 eulerRotation);
		void RotateAround(Vec3 positionToRotateAround, Quat rotation);
		Mat4 RotationMatrix() const;

		Vec3 GetScale() const;
		Vec3 GetPrevScale() const;
		void SetScale(Vec3 newScale);
		void Scale(Vec3 scaleFactor);

		Vec3 ToForwardVec() const;
		void MoveForward(float amount);

		Vec3 ToUpVec() const;
		void MoveUp(float amount);

		Vec3 ToRightVec() const;
		void MoveRight(float amount);

		Mat4 ModelMatrix() const;

		static constexpr const char* ComponentName()
		{
			return STRINGIFY(Transform);
		}

		virtual std::string GetComponentName() const override;

	private:
		Vec3 position;
		Quat orientation;
		Vec3 scale;

		Vec3 prevPosition;
		Quat prevOrientation;
		Vec3 prevScale;
	};
}

