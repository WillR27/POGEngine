#pragma once

#define GLM_FORCE_LEFT_HANDED

#include "POGMaths/Matrices.h"
#include "POGMaths/Quaternions.h"
#include "POGMaths/Vectors.h"

#include "POGMathsAPI.h"

namespace POG::Maths
{
	constexpr float TwoPi()
	{
		return glm::two_pi<float>();
	}

	constexpr float Pi()
	{
		return glm::pi<float>();
	}

	constexpr float HalfPi()
	{
		return glm::half_pi<float>();
	}

	template <typename T>
	static int Sign(T val)
	{
		return (T(0) < val) - (val < T(0));
	}

	// Coverts degrees to radians. Does not normalise.
	float ToRadians(float degrees);

	// Creates a model matrix from the passed parameters. 
	Mat4 ToModelMatrix(Vec3 position, Quat orientation, Vec3 scale);
}