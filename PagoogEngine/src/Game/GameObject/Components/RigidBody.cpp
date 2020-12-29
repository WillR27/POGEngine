#include "pgepch.h"
#include "RigidBody.h"

namespace PEngine
{
	RigidBody::RigidBody()
		: mass(1.0f)
		, force(Vec3(0.0f, 0.0f, 0.0f))
		, velocity(Vec3(0.0f, 0.0f, 0.0f))
	{
	}

	void RigidBody::UpdateRigidBody(float dt)
	{
		Vec3 acceleration = force / mass;
		velocity += acceleration * dt;

		ToTransform().Translate(velocity * dt);
	}

	float RigidBody::GetMass() const
	{
		return mass;
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

	Transform& RigidBody::ToTransform()
	{
		Transform* transform = dynamic_cast<Transform*>(this);
		PG_ASSERT(transform, "Rigid body does not have a transform to work with!");
		return *transform;
	}
}