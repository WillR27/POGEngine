#include "POGMathsPCH.h"
#include "Maths.h"

#include <glm/glm.hpp>

namespace POG::Maths
{
	float ToRadians(float degrees)
	{
		return glm::radians(degrees);
	}

	Mat4 ToModelMatrix(Vec3 position, Quat orientation, Vec3 scale)
	{
		Mat4 model(1.0f);
		model = Translate(model, position);
		model = Rotate(model, ToMatrix(orientation));
		model = Scale(model, scale);

		return model;
	}
}