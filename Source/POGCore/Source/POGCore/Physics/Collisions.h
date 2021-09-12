#pragma once

#include "POGMaths.h"

#include "POGCore/ECS/Components.h"

namespace POG::Core
{
	///////////////////////////////////////////////////////////////////////////////
	// HELPERS

	bool Contains(Maths::Vec2 min, Maths::Vec2 max, Maths::Vec2 point);

	BoxCollider2D ScaleBoxCollider2D(const BoxCollider2D& boxCollider, const Maths::Vec3& scale);
	RectCollider ScaleRectCollider(const RectCollider& rectCollider, const Maths::Vec3& scale);

	// HELPERS
	///////////////////////////////////////////////////////////////////////////////

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

	struct CollisionResult
	{
		bool collision = false;
		Maths::Vec3 displacement = Maths::Vec3(0.0f, 0.0f, 0.0f);
	};

	CollisionResult TestCollisionBoxCollider2D(const Transform& transform1, const BoxCollider2D& boxCollider1, const Transform& transform2, const BoxCollider2D& boxCollider2);

	CollisionResult Hits(const Transform& transform1, const RectCollider& rectCollider1, const Transform& transform2, const RectCollider& rectCollider2);
}

