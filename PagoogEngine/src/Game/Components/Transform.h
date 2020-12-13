#pragma once

#include "Maths/Maths.h"

namespace PEngine
{
	class Transform
	{
	public:
		Transform(Vec3 position = Vec3(0.0f, 0.0f, 0.0f), Quaternion orientation = Quaternion(), Vec3 scale = Vec3(1.0f, 1.0f, 1.0f));
		~Transform() = default;

		Vec3 GetPosition() const;
		void SetPosition(Vec3 newPosition);
		void Translate(Vec3 translation);

		Quaternion GetOrientation() const;
		void SetOrientation(Quaternion newOrientation);
		void SetOrientation(Vec3 newOrientation);

		void RotateAround(Vec3 positionToRotateAround, Quaternion rotation);

		Mat4 GetRotationMatrix() const;

		Vec3 GetScale() const;
		void SetScale(Vec3 newScale);
		void Scale(Vec3 scaleFactor);

	private:
		Vec3 position;
		Quaternion orientation;
		Vec3 scale;
	};
}

