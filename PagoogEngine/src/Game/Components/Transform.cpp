#include "pgepch.h"
#include "Transform.h"

namespace PEngine
{
	Transform::Transform(Vec3 position, Quaternion rotation, Vec3 scale)
		: position(position)
		, orientation(rotation)
		, scale(scale)
	{
	}

	void Transform::Translate(Vec3 translation)
	{
		position += (glm::vec3)translation;
	}

	Vec3 Transform::GetPosition() const
	{
		return position;
	}

	void Transform::SetPosition(Vec3 newPosition)
	{
		position = newPosition;
	}

	Quaternion Transform::GetOrientation() const
	{
		return orientation;
	}

	void Transform::SetOrientation(Quaternion newOrientation)
	{
		orientation = newOrientation;
	}

	void Transform::SetOrientation(Vec3 newOrientation)
	{
		orientation = Quaternion(newOrientation);
	}

	void Transform::Rotate(Quaternion rotation)
	{
		orientation = glm::normalize(rotation * orientation);
	}

	void Transform::RotateAround(Vec3 positionToRotateAround, Quaternion rotation)
	{
		Mat4 transformation(1.0f);
		transformation = Maths::Rotate(transformation, rotation);
		
		position -= positionToRotateAround;
		position = transformation * Vec4(position, 1.0f);
		position += positionToRotateAround;

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
		scale *= scaleFactor;
	}

	Mat4 Transform::ModelMatrix() const
	{
		Mat4 model = Mat4(1.0f);
		model = Maths::Translate(model, GetPosition());
		model = Maths::Rotate(model, RotationMatrix());
		return model;
	}
}