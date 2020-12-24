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
		operator const float* () const
		{
			return glm::value_ptr(*((glm::mat4*)this));
		}
	};


	template <auto L, typename T = float>
	class Vec : public glm::vec<L, T, glm::defaultp>
	{
		//using glm::vec<L, float, glm::defaultp>::vec<L, float, glm::defaultp>;

	public:
		operator const T* () const
		{
			return glm::value_ptr(*((glm::vec<L, T, glm::defaultp>*)this));
		}

		inline std::ostream& operator<<(std::ostream& os)
		{
			std::stringstream ss;
			ss << "Vec()";
			return os << ss.str();
		}
	};

	class Vec2 : public glm::vec2
	{
		using glm::vec2::vec2;

	public:
		operator const float* () const
		{
			return glm::value_ptr(*((glm::vec2*)this));
		}

		inline std::ostream& operator<<(std::ostream& os)
		{
			std::stringstream ss;
			ss << "Vec2(" << this->x << ", " << this->y << ")";
			return os << ss.str();
		}
	};

	class Vec3 : public glm::vec3
	{
		using glm::vec3::vec3;

	public:
		operator const float* () const
		{
			return glm::value_ptr(*((glm::vec3*)this));
		}

		inline std::ostream& operator<<(std::ostream& os)
		{
			std::stringstream ss;
			ss << "Vec3(" << this->x << ", " << this->y << ", " << this->z << ")";
			return os << ss.str();
		}
	};

	class Vec4 : public glm::vec4
	{
		using glm::vec4::vec4;

	public:
		operator const float* () const
		{
			return glm::value_ptr(*((glm::vec4*)this));
		}

		inline std::ostream& operator<<(std::ostream& os)
		{
			std::stringstream ss;
			ss << "Vec4(" << this->x << ", " << this->y << ", " << this->z << ", " << this->w << ")";
			return os << ss.str();
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
		static float ToRadians(float degrees);

		static Mat4 Translate(Mat4 matrix, Vec3 translation);

		static Mat4 Rotate(Mat4 matrix, float radians, Vec3 axisAmount);
		static Mat4 Rotate(Mat4 matrix, Quat quaternion);

		static Mat4 Scale(Mat4 matrix, Vec3 scale);

		static Vec3 Lerp(Vec3 start, Vec3 end, float a);
		static Quat Lerp(Quat  start, Quat end, float a);

		static Mat4 ToMatrix(Quat orientation);

		static Mat4 ToModelMatrix(Vec3 position, Quat orientation, Vec3 scale);

		static float DotProduct(Vec3 vec1, Vec3 vec2);
	};
}

