#pragma once

#include "BaseComponent.h"
#include "Maths/Maths.h"

namespace PEngine
{
	class Transform : public BaseComponent
	{
	public:
		Transform(Vec3 position = Vec3(0.0f, 0.0f, 0.0f), Quaternion orientation = Quaternion(), Vec3 scale = Vec3(1.0f, 1.0f, 1.0f));
		virtual ~Transform() = default;

		Vec3 GetPosition() const;
		void SetPosition(Vec3 newPosition);
		void Translate(Vec3 translation);
		Vec3 GetPrevPosition() const;
		void SetPrevPosition(Vec3 newPosition);

		Quaternion GetOrientation() const;
		Quaternion GetPrevOrientation() const;
		void SetOrientation(Vec3 newOrientation);
		void SetOrientation(Quaternion newOrientation);
		void SetPrevOrientation(Quaternion newOrientation);

		void Rotate(Quaternion rotation);
		void RotateAround(Vec3 positionToRotateAround, Quaternion rotation);
		Mat4 RotationMatrix() const;

		Vec3 GetScale() const;
		void SetScale(Vec3 newScale);
		void Scale(Vec3 scaleFactor);
		Vec3 GetPrevScale() const;
		void SetPrevScale(Vec3 newScale);

		Mat4 ModelMatrix() const;
		Mat4 PrevModelMatrix() const;

	private:
		Vec3 position;
		Quaternion orientation;
		Vec3 scale;

		Vec3 prevPosition;
		Quaternion prevOrientation;
		Vec3 prevScale;
	};
}

