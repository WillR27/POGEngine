#pragma once

#include "Maths/Maths.h"
#include "Game/GameObject/GameObject.h"

namespace PEngine
{
	class Transform : public virtual GameObject
	{
	public:
		Transform(Vec3 position = Vec3(0.0f, 0.0f, 0.0f), Quat orientation = Quat(Vec3(0.0f, 0.0f, 0.0f)), Vec3 scale = Vec3(1.0f, 1.0f, 1.0f));
		virtual ~Transform() = default;

		Vec3 GetPosition() const;
		Vec3 GetPrevPosition() const;
		void SetPosition(Vec3 newPosition);
		void Translate(Vec3 translation);

		Quat GetOrientation() const;
		Quat GetPrevOrientation() const;
		void SetOrientation(Vec3 newOrientation);
		void SetOrientation(Quat newOrientation);

		void Rotate(Quat rotation);
		void RotateAround(Vec3 positionToRotateAround, Quat rotation);
		Mat4 RotationMatrix() const;

		Vec3 GetScale() const;
		Vec3 GetPrevScale() const;
		void SetScale(Vec3 newScale);
		void Scale(Vec3 scaleFactor);

		Mat4 ModelMatrix() const;

	private:
		Vec3 position;
		Quat orientation;
		Vec3 scale;

		Vec3 prevPosition;
		Quat prevOrientation;
		Vec3 prevScale;
	};
}

