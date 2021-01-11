#pragma once

#include <glm.hpp>
#include <gtx/matrix_decompose.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
#include <gtx/string_cast.hpp>
#include <gtc/type_ptr.hpp>

#include "Vectors.h"

namespace PEngine
{
	class Mat4 : public glm::mat4
	{
		using glm::mat4::mat4;

	public:
		operator const float* () const
		{
			return glm::value_ptr(*((glm::mat4*)this));
		}
	};


	class Quat : public glm::quat
	{
		using glm::quat::quat;

	public:
	};


	template <unsigned int D = 3, typename T = float>
	struct Size
	{
	public:
		Size()
		{

		}

		Size(std::initializer_list<T> valuesList)
		{
			std::vector<T> v; // TODO: Fix this ugliness
			v.insert(v.end(), valuesList.begin(), valuesList.end());

			for (int d = 0; d < D; d++)
			{
				values[d] = v[d];
			}
		}

		Size(Vec<D> size)
			: values(size)
		{
		}

		T operator[](unsigned int index) const
		{
			if (index >= D)
			{
				PG_ASSERT(false, "Tried to access a dimension that didn't exist!");
			}

			return values[index];
		}

		int GetDimensions() const
		{
			return D;
		}

		Vec<D, T> ToVec() const
		{
			return values;
		}

	private:
		Vec<D, T> values;
	};


	class Maths
	{
	public:
		static constexpr float TwoPi()
		{
			return glm::two_pi<float>();
		}

		static constexpr float Pi()
		{
			return glm::pi<float>();
		}

		static constexpr float HalfPi()
		{
			return glm::half_pi<float>();
		}

		template <typename T> 
		static int Sign(T val) 
		{
			return (T(0) < val) - (val < T(0));
		}

		static float ToRadians(float degrees);

		static Vec3 Normalise(Vec3 vector);
		static Quat Normalise(Quat quaternion);

		static Mat4 Translate(Mat4 matrix, Vec3 translation);

		static Mat4 Rotate(Mat4 matrix, float radians, Vec3 axisAmount);
		static Mat4 Rotate(Mat4 matrix, Quat quaternion);

		static Mat4 Scale(Mat4 matrix, Vec3 scale);

		static Vec3 Lerp(Vec3 start, Vec3 end, float a);
		static Quat Lerp(Quat  start, Quat end, float a);

		static Mat4 ToMatrix(Quat orientation);

		static Mat4 ToModelMatrix(Vec3 position, Quat orientation, Vec3 scale);

		static float DotProduct(Vec3 vec1, Vec3 vec2);

		static Vec3 Vec3MultiplyPreserveSigns(Vec3 vec1, Vec3 vec2);

		static float DistanceSq(Vec3 vec);

		static Vec3 ToForwardVec(const Quat& quat);
		static Vec3 ToUpVec(const Quat& quat);
		static Vec3 ToRightVec(const Quat& quat);
	};
}

