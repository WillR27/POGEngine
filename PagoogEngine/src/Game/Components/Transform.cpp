#include "pgepch.h"
#include "Transform.h"

namespace PEngine
{
	Transform::Transform(Vec3 position, Quaternion rotation, Vec3 scale)
		: position(position)
		, orientation(rotation)
		, scale(scale)
		, prevPosition(position)
		, prevOrientation(orientation)
		, prevScale(scale)
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

	Vec3 Transform::GetPrevPosition() const
	{
		return prevPosition;
	}

	void Transform::SetPrevPosition(Vec3 newPosition)
	{
		prevPosition = newPosition;
	}

	Quaternion Transform::GetOrientation() const
	{
		return orientation;
	}

	void Transform::SetOrientation(Quaternion newOrientation)
	{
		orientation = newOrientation;
	}

	Quaternion Transform::GetPrevOrientation() const
	{
		return prevOrientation;
	}

	void Transform::SetPrevOrientation(Quaternion newOrientation)
	{
		prevOrientation = newOrientation;
	}

	void Transform::SetOrientation(Vec3 newOrientation)
	{
		SetOrientation(Quaternion(newOrientation));
	}

	void Transform::Rotate(Quaternion rotation)
	{
		SetOrientation(glm::normalize(rotation * orientation));
	}

	void Transform::RotateAround(Vec3 positionToRotateAround, Quaternion rotation)
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

	Vec3 Transform::GetPrevScale() const
	{
		return prevScale;
	}

	void Transform::SetPrevScale(Vec3 newScale)
	{
		prevScale = newScale;
	}

	Mat4 Transform::ModelMatrix() const
	{
		Mat4 model(1.0f);
		model = Maths::Translate(model, GetPosition());
		model = Maths::Rotate(model, RotationMatrix());
		return model;
	}

	Mat4 Transform::PrevModelMatrix() const
	{
		Mat4 model(1.0f);
		model = Maths::Translate(model, prevPosition);
		model = Maths::Rotate(model, Maths::ToMatrix(prevOrientation));
		return model;
	}
}