#include "pgepch.h"
#include "BoxCollider.h"

namespace PEngine
{
    BoxCollider::BoxCollider(std::initializer_list<float> dimensions)
        : aabb(dimensions)
    {
    }

    AABB<3> BoxCollider::GetAABB() const
    {
        return aabb;
    }
}