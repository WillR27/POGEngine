#include "pgepch.h"
#include "Transform.h"

namespace PEngine
{
	Transform::Transform(Vec3 position, Quat rotation, Vec3 scale)
		: position(position)
		, orientation(rotation)
		, scale(scale)
		, prevPosition(position)
		, prevOrientation(rotation)
		, prevScale(scale)
	{
	}

	void Transform::Translate(Vec3 translation)
	{
		SetPosition(position + translation);
	}

	Component* Transform::Clone() const
	{
		return new Transform(*this);
	}

	void Transform::PreInputUpdateTransform()
	{
		prevPosition = position;
		prevOrientation = orientation;
		prevScale = scale;
	}

	Vec3 Transform::GetPosition() const
	{
		return position;
	}

	Vec3 Transform::GetPrevPosition() const
	{
		return prevPosition;
	}

	void Transform::SetPosition(Vec3 newPosition)
	{
		prevPosition = position;
		position = newPosition;
	}

	Quat Transform::GetOrientation() const
	{
		return orientation;
	}

	Quat Transform::GetPrevOrientation() const
	{
		return prevOrientation;
	}

	void Transform::SetOrientation(Quat newOrientation)
	{
		prevOrientation = orientation;
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

	Vec3 Transform::GetPrevScale() const
	{
		return prevScale;
	}

	void Transform::SetScale(Vec3 newScale)
	{
		prevScale = scale;
		scale = newScale;
	}

	void Transform::Scale(Vec3 scaleFactor)
	{
		SetScale(scale * scaleFactor);
	}

	void Transform::MoveForward(float amount)
	{
		SetPosition(position + (Maths::ToForwardVector(orientation) * amount));
	}

	void Transform::MoveUp(float amount)
	{
		SetPosition(position + (Maths::ToUpVector(orientation) * amount));
	}

	void Transform::MoveRight(float amount)
	{
		SetPosition(position + (Maths::ToRightVector(orientation) * amount));
	}

	Mat4 Transform::ModelMatrix() const
	{
		return Maths::ToModelMatrix(position, orientation, scale);
	}

	std::string Transform::GetComponentName() const
	{
		return ComponentName();
	}
}