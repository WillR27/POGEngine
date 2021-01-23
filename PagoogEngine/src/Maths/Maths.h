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
			PG_ASSERT(index < D, "Tried to access a dimension [{0}] that didn't exist for Size with {1} dimensions!", index, D);
		
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

		// Coverts degrees to radians. Does not normalise.
		static float ToRadians(float degrees);

		// Normalises the given vector.
		static Vec3 Normalise(Vec3 vector);
		// Normalises the given quaternion.
		static Quat Normalise(Quat quaternion);

		// Translates the given matrix by the given translation vector.
		static Mat4 Translate(Mat4 matrix, Vec3 translation);

		// Rotates the given matrix by the given amounts. Largest absolute value for axisAmount determines axis.
		static Mat4 Rotate(Mat4 matrix, float radians, Vec3 axisAmount);
		// Rotates a given matrix by the given quaternion.
		static Mat4 Rotate(Mat4 matrix, Quat quaternion);

		// Scales the given matrix by the given vector.
		static Mat4 Scale(Mat4 matrix, Vec3 scale);

		// Linearly interpolates between two vectors.
		static Vec3 Lerp(Vec3 start, Vec3 end, float a);
		// Linearly interpolates between two quaternions.
		static Quat Lerp(Quat  start, Quat end, float a);

		// Converts a quaternion to a matrix.
		static Mat4 ToMatrix(Quat orientation);

		// Creates a model matrix from the passed parameters. 
		static Mat4 ToModelMatrix(Vec3 position, Quat orientation, Vec3 scale);

		// Returns the dot product of two vectos.
		static float DotProduct(Vec3 vec1, Vec3 vec2);

		// Multiplies two vectors together using the absolute values, but preserves the signage.
		static Vec3 Vec3MultiplyPreserveSigns(Vec3 vec1, Vec3 vec2);

		// Returns the distance squared of the given vector.
		static float DistanceSq(Vec3 vec);

		// Returns the forward directional vector for the given quaternion.
		static Vec3 ToForwardVec(const Quat& quat);
		// Returns the up directional vector for the given quaternion.
		static Vec3 ToUpVec(const Quat& quat);
		// Returns the right directional vector for the given quaternion.
		static Vec3 ToRightVec(const Quat& quat);
	};
}

