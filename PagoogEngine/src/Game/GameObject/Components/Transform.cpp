#include "pgepch.h"
#include "Transform.h"

namespace PEngine
{
	Transform::Transform(Vec3 position, Quat rotation, Vec3 scale)
		: position(position)
		, orientation(rotation)
		, scale(scale)
	{
	}

	void Transform::Translate(Vec3 translation)
	{
		SetPosition(position + translation);
	}

	Vec3 Transform::GetPosition() const
	{
		return position;
	}

	void Transform::SetPosition(Vec3 newPosition)
	{
		position = newPosition;
	}

	Quat Transform::GetOrientation() const
	{
		return orientation;
	}

	void Transform::SetOrientation(Quat newOrientation)
	{
		orientation = newOrientation;
	}

	void Transform::SetOrientation(Vec3 newOrientation)
	{
		SetOrientation(Quat(newOrientation));
	}

	void Transform::Rotate(Quat rotation)
	{
		SetOrientation(glm::normalize(rotation * orientation));
	}

	void Transform::RotateAround(Vec3 positionToRotateAround, Quat rotation)
	{
		Mat4 transformation(1.0f);
		transformation = Maths::Rotate(transformation, rotation);
		
		Translate(-positionToRotateAround);
		SetPosition(transformation * Vec4(position, 1.0f));
		Translate(positionToRotateAround);

		Rotate(rotation);
	}

	Mat4 Transform::RotationMatrix() const
	{
		return Maths::ToMatrix(orientation);
	}

	Vec3 Transform::GetScale() const
	{
		return scale;
	}

	void Transform::SetScale(Vec3 newScale)
	{
		scale = newScale;
	}

	void Transform::Scale(Vec3 scaleFactor)
	{
		SetScale(scale * scaleFactor);
	}

	Mat4 Transform::ModelMatrix() const
	{
		return Maths::ToModelMatrix(position, orientation, scale);
	}
}