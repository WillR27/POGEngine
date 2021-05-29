#include "POGMathsPCH.h"
#include "Matrices.h"

#include <glm/gtc/type_ptr.hpp>

#include "Quaternions.h"

namespace POG::Maths
{
	const float* ToData(Mat4 matrix)
	{
		return glm::value_ptr(*((glm::mat4*)&matrix));
	}

	Mat4 Translate(Mat4 matrix, Vec3 translation)
	{
		return glm::translate(matrix, translation);
	}

	Mat4 Rotate(Mat4 matrix, float radians, Vec3 axisAmount)
	{
		return glm::rotate(matrix, radians, axisAmount);
	}

	Mat4 Rotate(Mat4 matrix, Quat quaternion)
	{
		return matrix * ToMatrix(quaternion);
	}

	Mat4 Scale(Mat4 matrix, Vec3 scale)
	{
		return glm::scale(static_cast<glm::mat4>(matrix), static_cast<glm::vec3>(scale));
	}
}
