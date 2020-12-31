#pragma once

#include "Maths/Collisions.h"
#include "Game/GameObject/Components/Component.h"

namespace PEngine
{
	class BoxCollider : public Component
	{
	public:
		BoxCollider(std::initializer_list<float> dimensions = {1.0f, 1.0f, 1.0f});
		virtual ~BoxCollider() override = default;

		void CollideWith(BoxCollider& boxCollider);

		AABB<3> GetAABB() const;
		AABB<3> GetTransformedAABB() const;

		static constexpr const char* ComponentName()
		{
			return STRINGIFY(BoxCollider);
		}

		virtual std::string GetComponentName() const override;

	private:
		AABB<3> aabb;
	};
}

