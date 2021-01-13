#include "pgepch.h"
#include "BoxCollider.h"

#include "Game/GameObject/GameObject.h"
#include "Game/GameObject/Components/Components.h"

namespace PEngine
{
    BoxCollider::BoxCollider(std::initializer_list<float> dimensions)
        : aabb(dimensions)
		, stickiness(0.0f)
    {
    }

	_Component* BoxCollider::Clone() const
	{
		return new BoxCollider(*this);
	}

	void BoxCollider::CollideWith(BoxCollider& boxCollider)
	{
		auto transform1 = gameObject->GetComponent<Transform>();
		auto transform2 = boxCollider.gameObject->GetComponent<Transform>();

		const AABB<3>& aabb1 = GetTransformedAABB(*transform1);
		const AABB<3>& aabb2 = boxCollider.GetTransformedAABB(*transform2);

		Shared<Hit> hit = aabb1.IsCollidingWith2(aabb2);

		if (hit)
		{
			transform1->Translate(-hit->overlap);

			auto rigidBody1 = gameObject->GetComponent<RigidBody>();
			if (!rigidBody1.Exists())
			{
				return;
			}

			auto rigidBody2 = boxCollider.gameObject->GetComponent<RigidBody>();
			if (!rigidBody2.Exists())
			{
				return;
			}

			Vec3 position1 = transform1->GetPosition();
			Vec3 position2 = transform2->GetPosition();

			Vec3 velocity1 = rigidBody1->GetVelocity();
			Vec3 velocity2 = rigidBody2->GetVelocity();

			float mass1 = rigidBody1->GetMass();
			float mass2 = rigidBody2->GetMass();

			// This gives us the direction of the collision from 1 to 2
			//Vec3 collisionDirection = Maths::Normalise(position2 - position1);
			Vec3 collisionDirection = hit->surfaceNormal;

			// This gives us the relative velocity from 2 to 1
			Vec3 relativeVelocity = velocity1 - velocity2;

			// The speed of the collision is the dot product between the collision direction and the relative velocity
			float speedOfCollision = Maths::DotProduct(collisionDirection, relativeVelocity);

			float coefficientOfRestitution = (2.0f - (this->stickiness + boxCollider.stickiness)) / 2.0f;
			float speedAfterCollision = coefficientOfRestitution * speedOfCollision;

			if (speedAfterCollision <= 0.0f)
			{
				return;
			}

			float impulse = speedAfterCollision / (mass1 + mass2);
			Vec3 changeInVelocity1 = -impulse * mass1 * collisionDirection;
			Vec3 changeInVelocity2 =  impulse * mass1 * collisionDirection;

			rigidBody1->AddVelocity(changeInVelocity1);
			rigidBody2->AddVelocity(changeInVelocity2);
		}
	}

	AABB<3> BoxCollider::GetAABB() const
    {
        return aabb;
    }

	AABB<3> BoxCollider::GetTransformedAABB(const Transform& transform) const
	{
		Vec3 min(transform.GetPosition());
		min.x -= aabb.GetRadii()[0];		
		min.y -= aabb.GetRadii()[1];
		min.z -= aabb.GetRadii()[2];

		Vec3 max(transform.GetPosition());
		max.x += aabb.GetRadii()[0];
		max.y += aabb.GetRadii()[1];
		max.z += aabb.GetRadii()[2];

		return AABB<3>(min, max);
	}

	AABB<3> BoxCollider::GetTransformedAABB() const
	{
		return GetTransformedAABB(*gameObject->GetComponent<Transform>());
	}

	float BoxCollider::GetStickiness() const
	{
		return stickiness;
	}

	void BoxCollider::SetStickiness(float newStickiness)
	{
		PG_ASSERT(newStickiness >= 0.0f && newStickiness <= 1.0f, "Tried to set a box collider's stickiness to '{0}', which is outside the range 0-1!", newStickiness);

		this->stickiness = newStickiness;
	}

	std::string BoxCollider::GetComponentName() const
	{
		return ComponentName();
	}
}