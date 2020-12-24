#pragma once

#include "BaseComponent.h"
#include "Transform.h"

#include "Maths/Maths.h"

namespace PEngine
{
	class RigidBody : public BaseComponent
	{
	public:
		RigidBody();
		virtual ~RigidBody() = default;

		void Update(float dt);

		Vec3 GetForce() const;
		void SetForce(Vec3 newForce);

	private:
		float mass;
		Vec3 force;
		Vec3 velocity;

		Transform& ToTransform();
	};
}

