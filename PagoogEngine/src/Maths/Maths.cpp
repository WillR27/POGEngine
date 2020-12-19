#include "pgepch.h"
#include "Maths/Maths.h"

namespace PEngine
{
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
	Mat4 Maths::Rotate(Mat4 matrix, Quat quaternion)
	{
		return matrix * ToMatrix(quaternion);
	}

	/// <summary>
	/// Scales the given matrix by the given vector.
	/// </summary>
	Mat4 Maths::Scale(Mat4 matrix, Vec3 scale)
	{
		return glm::scale(static_cast<glm::mat4>(matrix), static_cast<glm::vec3>(scale));
	}

	/// <summary>
	/// Linearly interpolates between two vectors.
	/// </summary>
	Vec3 Maths::Lerp(Vec3 start, Vec3 end, float a)
	{
		return glm::mix(static_cast<glm::vec3>(start), static_cast<glm::vec3>(end), a);
	}

	/// <summary>
	/// Linearly interpolates between two quaternions.
	/// </summary>
	Quat Maths::Lerp(Quat start, Quat end, float a)
	{
		return glm::mix(static_cast<glm::quat>(start), static_cast<glm::quat>(end), a);
	}

	/// <summary>
	/// Converts a quaternion to a matrix.
	/// </summary>
	Mat4 Maths::ToMatrix(Quat orientation)
	{
		return glm::toMat4(static_cast<glm::quat>(orientation));
	}

	/// <summary>
	/// Creates a model matrix from the passed parameters. 
	/// </summary>
	Mat4 Maths::ToModelMatrix(Vec3 position, Quat orientation, Vec3 scale)
	{
		Mat4 model(1.0f);
		model = Translate(model, position);
		model = Rotate(model, ToMatrix(orientation));
		model = Scale(model, scale);
		return model;
	}
}
