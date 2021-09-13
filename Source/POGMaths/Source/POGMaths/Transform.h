#pragma once

#include "Maths.h"

namespace POG::Maths
{
	struct Transform
	{
		Vec3 position = Maths::Vec3(0.0f, 0.0f, 0.0f);
		Quat orientation = Maths::Quat(Maths::Vec3(0.0f, 0.0f, 0.0f));
		Vec3 scale = Maths::Vec3(1.0f, 1.0f, 1.0f);

		Vec2 ApplyTransform(Vec2 vec) const;
		Vec3 ApplyTransform(Vec3 vec) const;
		Vec4 ApplyTransform(Vec4 vec) const;
	};
}

