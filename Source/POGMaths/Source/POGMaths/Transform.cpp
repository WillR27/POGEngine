#include "POGMathsPCH.h"
#include "Transform.h"

namespace POG::Maths
{
	Vec2 Transform::ApplyTransform(Vec2 vec) const
	{
		Mat4 modelMatrix = ToModelMatrix(position, orientation, scale);
		Vec4 tempVec(vec.x, vec.y, 0.0f, 1.0f);
		return ApplyTransform(tempVec);
	}

	Vec3 Transform::ApplyTransform(Vec3 vec) const
	{
		Mat4 modelMatrix = ToModelMatrix(position, orientation, scale);
		Vec4 tempVec(vec.x, vec.y, vec.z, 1.0f);
		return ApplyTransform(tempVec);
	}

	Vec4 Transform::ApplyTransform(Vec4 vec) const
	{
		Mat4 modelMatrix = ToModelMatrix(position, orientation, scale);
		return modelMatrix * vec;
	}
}