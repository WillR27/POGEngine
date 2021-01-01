#include "pgepch.h"
#include "RigidBody.h"

#include "Game/GameObject/GameObject.h"

namespace PEngine
{
	RigidBody::RigidBody()
		: mass(1.0f)
		, dragCoef(1.0f)
		, force(Vec3(0.0f, 0.0f, 0.0f))
		, velocity(Vec3(0.0f, 0.0f, 0.0f))
	{
	}

	Component* RigidBody::Clone() const
	{
		return new RigidBody(*this);
	}

	void RigidBody::UpdateRigidBody(float dt)
	{
		Vec3 drag = dragCoef * Maths::Vec3MultiplyPreserveSigns(velocity, velocity);
		Vec3 acceleration = (force - drag) / mass;
		velocity += acceleration * dt;
		velocity.y = abs(velocity.y) > 0.01f ? velocity.y : 0.0f;
		velocity.z = abs(velocity.z) > 0.01f ? velocity.z : 0.0f;
		velocity.x = abs(velocity.x) > 0.01f ? velocity.x : 0.0f;

		gameObject->GetComponent<Transform>()->Translate(velocity * dt);
	}

	void RigidBody::SetMass(float newMass)
	{
		PG_ASSERT((newMass > 0.0f), "Tried to set mass to a value not greater than 0!");

		this->mass = newMass;
	}

	float RigidBody::GetMass() const
	{
		return mass;
	}

	void RigidBody::SetDragCoef(float newDragCoef)
	{
		this->dragCoef = newDragCoef;
	}

	float RigidBody::GetDragCoef() const
	{
		return dragCoef;
	}

	Vec3 RigidBody::GetForce() const
	{
		return force;
	}

	void RigidBody::SetForce(Vec3 newForce)
	{
		force = newForce;
	}

	void RigidBody::AddForce(Vec3 force)
	{
		this->force += force;
	}

	Vec3 RigidBody::GetVelocity() const
	{
		return velocity;
	}

	void RigidBody::SetVelocity(Vec3 newVelocity)
	{
		velocity = newVelocity;
	}

	void RigidBody::AddVelocity(Vec3 velocity)
	{
		this->velocity += velocity;
	}

	std::string RigidBody::GetComponentName() const
	{
		return ComponentName();
	}
}