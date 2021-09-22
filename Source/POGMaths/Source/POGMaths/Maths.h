#pragma once

#define GLM_FORCE_LEFT_HANDED

#include "Matrices.h"
#include "Quaternions.h"
#include "Vectors.h"

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

	static inline constexpr int Min(int a, int b)
	{
		return a < b ? a : b;
	}
	static inline constexpr int Max(int a, int b)
	{
		return a > b ? a : b;
	}

	static inline constexpr float Min(float a, float b)
	{
		return a < b ? a : b;
	}
	static inline constexpr float Max(float a, float b)
	{
		return a > b ? a : b;
	}

	static inline constexpr int IsOdd(int x) 
	{ 
		return x & 1; 
	}

	static inline constexpr int DivideRoundDown(int a, int b)
	{
		return a / b - (a % b < 0 ? 1 : 0);
	}
}