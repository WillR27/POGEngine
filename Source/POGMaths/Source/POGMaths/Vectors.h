#pragma once

#include <glm/gtx/rotate_vector.hpp>

#include "Matrix.h"
#include "Quaternion.h"
#include "Vector.h"

namespace POG::Maths
{
	template<glm::length_t L, typename T, glm::qualifier Q>
	Vec<L, T, Q> Cross(const Vec<L, T, Q>& x, const Vec<L, T, Q>& y)
	{
		return glm::cross(x, y);
	}

	float* ToDataRef(Vec3& vec);

	// Normalises the given vector.
	Vec3 Normalise(Vec3 vector);

	// Linearly interpolates between two vectors.
	Vec3 Lerp(Vec3 start, Vec3 end, float a);

	// Returns the magnitude of a vector.
	float Length(Vec3 vec1);

	// Returns the scalar product of two vectors.
	float ScalarProduct(Vec3 vec1, Vec3 vec2);

	// Returns the dot product of two vectors.
	float DotProduct(Vec3 vec1, Vec3 vec2);

	// Multiplies two vectors together using the absolute values, but preserves the signage.
	Vec3 Vec3MultiplyPreserveSigns(Vec3 vec1, Vec3 vec2);

	// Returns the distance squared of the given vector.
	float DistanceSq(Vec3 vec);
}