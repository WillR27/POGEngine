#pragma once

#include "POGMaths.h"

#include "POGCore/ECS/Components.h"

namespace POG::Core
{
	struct Ray
	{
		Maths::Vec3 origin = Maths::Vec3(0.0f, 0.0f, 0.0f);
		Maths::Vec3 direction = Maths::Vec3(0.0f, 0.0f, 1.0f);
	};

	struct RayResult
	{
		bool hit = false;
		Maths::Vec3 pointOfIntersection = Maths::Vec3(0.0f, 0.0f, 0.0f);
	};

	struct RayResultRectCollider : public RayResult
	{
		Maths::Vec2 pointOnRect = Maths::Vec2(0.0f, 0.0f);
	};

	RayResultRectCollider Hits(const Ray& ray, const Transform& transform, const RectCollider& rectCollider, const Sprite& sprite);
	RayResultRectCollider Hits(const Ray& ray, const Transform& transform, const RectCollider& rectCollider);

	Ray CalcMouseRay(Maths::Vec3 origin);
}

