#pragma once

#include "Transform.h"
#include "Maths/Maths.h"
#include "Game/GameObject/GameObject.h"

namespace PEngine
{
	class RigidBody : public virtual GameObject
	{
	public:
		RigidBody();
		virtual ~RigidBody() = default;

		void UpdateRigidBody(float dt);

		float GetMass() const;

		Vec3 GetForce() const;
		void SetForce(Vec3 newForce);

		Vec3 GetVelocity() const;
		void SetVelocity(Vec3 newVelocity);
		void AddVelocity(Vec3 velocity);

	private:
		float mass;
		Vec3 force;
		Vec3 velocity;

		Transform& ToTransform();
	};
}

