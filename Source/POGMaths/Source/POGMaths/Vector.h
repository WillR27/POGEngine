#pragma once

namespace POG::Maths
{
	template<glm::length_t L, typename T, glm::qualifier Q>
	using Vec = glm::vec<L, T, Q>;

	using Vec1 = Vec<1, float, glm::defaultp>;
	using Vec2 = Vec<2, float, glm::defaultp>;
	using Vec3 = Vec<3, float, glm::defaultp>;
	using Vec4 = Vec<4, float, glm::defaultp>;

	using Vec1i = Vec<1, int, glm::defaultp>;
	using Vec2i = Vec<2, int, glm::defaultp>;
	using Vec3i = Vec<3, int, glm::defaultp>;
	using Vec4i = Vec<4, int, glm::defaultp>;
}