#include "pgepch.h"
#include "BoxCollider.h"

namespace PEngine
{
    BoxCollider::BoxCollider(std::initializer_list<float> dimensions)
        : aabb(dimensions)
    {
    }

	void BoxCollider::CollideWith(BoxCollider& boxCollider)
	{
		const AABB<3>& aabb1 = GetAABB();
		const AABB<3>& aabb2 = boxCollider.GetAABB();
	}

	AABB<3> BoxCollider::GetAABB() const
    {
        return aabb;
    }
}