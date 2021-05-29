#pragma once

#include "Matrix.h"
#include "Quaternion.h"
#include "Vector.h"

namespace POG::Maths
{
	float* ToDataRef(Quat& quat);

	// Normalises the given quaternion.
	Quat Normalise(Quat quaternion);

	// Linearly interpolates between two quaternions.
	Quat Lerp(Quat start, Quat end, float a);

	// Converts a quaternion to a matrix.
	Mat4 ToMatrix(Quat orientation);

	// Returns the forward directional vector for the given quaternion.
	Vec3 ToForwardVec(const Quat& quat);
	// Returns the up directional vector for the given quaternion.
	Vec3 ToUpVec(const Quat& quat);
	// Returns the right directional vector for the given quaternion.
	Vec3 ToRightVec(const Quat& quat);
}