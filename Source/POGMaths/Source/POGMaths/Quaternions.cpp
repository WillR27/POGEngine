#include "POGMathsPCH.h"
#include "Quaternions.h"

namespace POG::Maths
{
	Quat Normalise(Quat quaternion)
	{
		return glm::normalize(quaternion);
	}

	Quat Lerp(Quat start, Quat end, float a)
	{
		return glm::mix(static_cast<glm::quat>(start), static_cast<glm::quat>(end), a);
	}

	Mat4 ToMatrix(Quat orientation)
	{
		return glm::toMat4(static_cast<glm::quat>(orientation));
	}

	Vec3 ToForwardVec(const Quat& quat)
	{
		return glm::rotate(quat, Vec3(0.0f, 0.0f, 1.0f));
	}

	Vec3 ToUpVec(const Quat& quat)
	{
		return glm::rotate(quat, Vec3(0.0f, 1.0f, 0.0f));
	}

	Vec3 ToRightVec(const Quat& quat)
	{
		return glm::rotate(quat, Vec3(1.0f, 0.0f, 0.0f));
	}
}
