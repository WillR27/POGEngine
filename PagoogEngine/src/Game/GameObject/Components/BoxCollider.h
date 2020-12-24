#pragma once

#include "Maths/Collisions.h"
#include "Game/GameObject/GameObject.h"

namespace PEngine
{
	class BoxCollider : public virtual GameObject
	{
	public:
		BoxCollider(std::initializer_list<float> dimensions = {1.0f, 1.0f, 1.0f});
		~BoxCollider() override = default;

		AABB<3> GetAABB() const;

	private:
		AABB<3> aabb;
	};
}

