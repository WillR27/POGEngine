#pragma once

#include "Matrix.h"
#include "Quaternion.h"
#include "Vector.h"

namespace POG::Maths
{
	const float* ToData(Mat4 matrix);

	// Translates the given matrix by the given translation vector.
	Mat4 Translate(Mat4 matrix, Vec3 translation);

	// Rotates the given matrix by the given amounts. Largest absolute value for axisAmount determines axis.
	Mat4 Rotate(Mat4 matrix, float radians, Vec3 axisAmount);
	// Rotates a given matrix by the given quaternion.
	Mat4 Rotate(Mat4 matrix, Quat quaternion);

	// Scales the given matrix by the given vector.
	Mat4 Scale(Mat4 matrix, Vec3 scale);
}