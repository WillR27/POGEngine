#include "pgepch.h"

namespace PEngine
{
	/*Transform::Transform(Vec3 position, Quat rotation, Vec3 scale)
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

	void Transform::PreInputUpdate()
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
		orientation = Maths::Normalise(newOrientation);
	}

	void Transform::SetOrientation(Vec3 newOrientation)
	{
		SetOrientation(Quat(newOrientation));
	}

	void Transform::Rotate(Quat rotation)
	{
		SetOrientation(rotation * orientation);
	}

	void Transform::Rotate(Vec3 eulerRotation)
	{
		Rotate(Quat(eulerRotation));
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

	Vec3 Transform::ToForwardVec() const
	{
		return Maths::ToForwardVec(orientation);
	}

	void Transform::MoveForward(float amount)
	{
		SetPosition(position + (ToForwardVec() * amount));
	}

	Vec3 Transform::ToUpVec() const
	{
		return Maths::ToUpVec(orientation);
	}

	void Transform::MoveUp(float amount)
	{
		SetPosition(position + (ToUpVec() * amount));
	}

	Vec3 Transform::ToRightVec() const
	{
		return Maths::ToRightVec(orientation);
	}

	void Transform::MoveRight(float amount)
	{
		SetPosition(position + (ToRightVec() * amount));
	}

	Mat4 Transform::ModelMatrix() const
	{
		return Maths::ToModelMatrix(position, orientation, scale);
	}

	std::string Transform::GetComponentName() const
	{
		return ComponentName();
	}*/
}