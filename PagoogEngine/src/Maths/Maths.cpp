#include "pgepch.h"
#include "Maths/Maths.h"

namespace PEngine
{
	Mat4::operator const float* () const
	{
		return glm::value_ptr(*((glm::mat4*)this));
	}

	/// <summary>
	/// Coverts degrees to radians. Does not normalise.
	/// </summary>
	float Maths::ToRadians(float degrees)
	{
		return glm::radians(degrees);
	}

	/// <summary>
	/// Translates the given matrix by the given translation vector.
	/// </summary>
	Mat4 Maths::Translate(Mat4 matrix, Vec3 translation)
	{
		return glm::translate(matrix, translation);
	}

	/// <summary>
	/// Rotates the given matrix by the given amounts. Largest absolute value for axisAmount determines axis.
	/// </summary>
	Mat4 Maths::Rotate(Mat4 matrix, float radians, Vec3 axisAmount)
	{
		return glm::rotate(matrix, radians, axisAmount);
	}

	/// <summary>
	/// Rotates a given matrix by the given quaternion.
	/// </summary>
	Mat4 Maths::Rotate(Mat4 matrix, Quaternion quaternion)
	{
		return matrix * ToMatrix(quaternion);
	}

	/// <summary>
	/// Converts a quaternion to a matrix.
	/// </summary>
	Mat4 Maths::ToMatrix(Quaternion orientation)
	{
		return glm::toMat4(orientation);
	}
}
