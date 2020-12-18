#pragma once

#include <glm.hpp>
#include <gtx/matrix_decompose.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
#include <gtx/string_cast.hpp>
#include <gtc/type_ptr.hpp>

namespace PEngine
{
	class Mat4 : public glm::mat4
	{
		using glm::mat4::mat4;

	public:
		operator const float* () const;
	};

	typedef glm::vec2 Vec2;
	typedef glm::vec3 Vec3;
	typedef glm::vec4 Vec4;

	typedef glm::quat Quaternion;


	class Maths
	{
	public:
		static float ToRadians(float degrees);

		static Mat4 Translate(Mat4 matrix, Vec3 translation);

		static Mat4 Rotate(Mat4 matrix, float radians, Vec3 axisAmount);
		static Mat4 Rotate(Mat4 matrix, Quaternion quaternion);

		static Mat4 Scale(Mat4 matrix, Vec3 scale);

		static Vec3 Lerp(Vec3 start, Vec3 end, float a);
		static Quaternion Lerp(Quaternion  start, Quaternion end, float a);

		static Mat4 ToMatrix(Quaternion orientation);

		static Mat4 ToModelMatrix(Vec3 position, Quaternion orientation, Vec3 scale);
	};
}

