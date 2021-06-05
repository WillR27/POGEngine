#include "POGMathsPCH.h"
#include "Vectors.h"

#include <glm/gtc/type_ptr.hpp>

namespace POG::Maths
{
	float* ToDataRef(Vec3& vec)
	{
		return glm::value_ptr(*((glm::vec3*)&vec));
	}

	Vec3 Normalise(Vec3 vector)
	{
		return glm::normalize(vector);
	}

	Vec3 Lerp(Vec3 start, Vec3 end, float a)
	{
		return glm::mix(static_cast<glm::vec3>(start), static_cast<glm::vec3>(end), a);
	}

	float Length(Vec3 vec1)
	{
		return glm::length(vec1);
	}

	float ScalarProduct(Vec3 vec1, Vec3 vec2)
	{
		return Length(vec1) * Length(vec2);
	}

	float DotProduct(Vec3 vec1, Vec3 vec2)
	{
		return glm::dot(static_cast<glm::vec3>(vec1), static_cast<glm::vec3>(vec2));
	}

	Vec3 Vec3MultiplyPreserveSigns(Vec3 vec1, Vec3 vec2)
	{
		Vec3 retVec;
		retVec.x = abs(vec1.x) * vec2.x;
		retVec.y = abs(vec1.y) * vec2.y;
		retVec.z = abs(vec1.z) * vec2.z;
		return retVec;
	}

	float DistanceSq(Vec3 vec)
	{
		return DotProduct(vec, vec);
	}
}
