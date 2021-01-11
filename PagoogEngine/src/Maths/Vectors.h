#pragma once

#include <glm.hpp>
#include <gtx/string_cast.hpp>
#include <gtc/type_ptr.hpp>

namespace PEngine
{
	//template<glm::length_t L>
	//using Vec = glm::vec<L, float, glm::packed_highp>;

	//using Vec2 = glm::vec2;
	//using Vec3 = glm::vec3;
	//using Vec4 = glm::vec4;

	template<int L, typename T = float>
	using Vec = glm::vec<L, T, glm::packed_highp>;

	class Vec2 : public glm::vec2
	{
		using glm::vec2::vec2;

	public:
		operator const float* () const
		{
			return glm::value_ptr(*((glm::vec2*)this));
		}

		void operator+=(const Vec2& rhs)
		{
			this->x += rhs.x;
			this->y += rhs.y;
		}

		void operator-=(const Vec2& rhs)
		{
			this->x -= rhs.x;
			this->y -= rhs.y;
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

		void operator+=(const Vec3& rhs)
		{
			this->x += rhs.x;
			this->y += rhs.y;
			this->z += rhs.z;
		}

		void operator-=(const Vec3& rhs)
		{
			this->x -= rhs.x;
			this->y -= rhs.y;
			this->z -= rhs.z;
		}

		Vec3 operator*(const Vec3& rhs)
		{
			return Vec3(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z);
		}

		std::string ToString() const
		{
			std::stringstream ss;
			ss << "Vec3(" << this->x << ", " << this->y << ", " << this->z << ")";
			return ss.str();
		}

		inline std::ostream& operator<<(std::ostream& os)
		{
			return os << ToString();
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

		void operator+=(const Vec4& rhs)
		{
			this->x += rhs.x;
			this->y += rhs.y;
			this->z += rhs.z;
			this->w += rhs.w;
		}

		void operator-=(const Vec4& rhs)
		{
			this->x -= rhs.x;
			this->y -= rhs.y;
			this->z -= rhs.z;
			this->w -= rhs.w;
		}

		inline std::ostream& operator<<(std::ostream& os)
		{
			std::stringstream ss;
			ss << "Vec4(" << this->x << ", " << this->y << ", " << this->z << ", " << this->w << ")";
			return os << ss.str();
		}
	};
}