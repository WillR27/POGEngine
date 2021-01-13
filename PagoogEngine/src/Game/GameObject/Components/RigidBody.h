#pragma once

#include "Transform.h"
#include "Maths/Maths.h"
#include "Game/GameObject/Components/Component.h"

namespace PEngine
{
	class RigidBody : public _Component
	{
	public:
		RigidBody();
		virtual ~RigidBody() = default;

		virtual _Component* Clone() const override;

		void Update(float dt);

		void SetMass(float newMass);
		float GetMass() const;

		void SetDragCoef(float newDragCoef);
		float GetDragCoef() const;

		Vec3 GetForce() const;
		void SetForce(Vec3 newForce);
		void AddForce(Vec3 force);

		Vec3 GetVelocity() const;
		void SetVelocity(Vec3 newVelocity);
		void AddVelocity(Vec3 velocity);

		static constexpr const char* ComponentName()
		{
			return STRINGIFY(RigidBody);
		}

		virtual std::string GetComponentName() const override;

	private:
		float mass;
		float dragCoef;
		Vec3 force;
		Vec3 velocity;
	};
}

