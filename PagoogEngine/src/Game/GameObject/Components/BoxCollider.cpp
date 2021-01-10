#include "pgepch.h"
#include "BoxCollider.h"

#include "Game/GameObject/GameObject.h"
#include "Game/GameObject/Components/Components.h"

namespace PEngine
{
    BoxCollider::BoxCollider(std::initializer_list<float> dimensions)
        : aabb(dimensions)
    {
    }

	Component* BoxCollider::Clone() const
	{
		return new BoxCollider(*this);
	}

	void BoxCollider::CollideWith(BoxCollider& boxCollider)
	{
		Transform& transform1 = *gameObject->GetComponent<Transform>();
		PG_ASSERT(&transform1, gameObject->GetName() + " has a box collider component but no transform component!");
		Transform& transform2 = *boxCollider.gameObject->GetComponent<Transform>();
		PG_ASSERT(&transform2, boxCollider.gameObject->GetName() + " has a box collider component but no transform component!");

		const AABB<3>& aabb1 = GetTransformedAABB(transform1);
		const AABB<3>& aabb2 = boxCollider.GetTransformedAABB(transform2);

		Shared<Hit> hit = aabb1.IsCollidingWith2(aabb2);

		if (hit)
		{
			transform1.Translate(-hit->overlap);

			RigidBody* rigidBody1 = gameObject->GetComponent<RigidBody>();
			if (rigidBody1 == nullptr)
			{
				return;
			}

			RigidBody* rigidBody2 = boxCollider.gameObject->GetComponent<RigidBody>();
			if (rigidBody2 == nullptr)
			{
				return;
			}

			Vec3 position1 = transform1.GetPosition();
			Vec3 position2 = transform2.GetPosition();

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

			if (speedOfCollision <= 0.0f)
			{
				return;
			}

			float impulse = speedOfCollision / (mass1 + mass2);
			Vec3 changeInVelocity1 = -impulse * mass1 * collisionDirection;
			Vec3 changeInVelocity2 =  impulse * mass1 * collisionDirection;

			rigidBody1->AddVelocity(changeInVelocity1);
			rigidBody2->AddVelocity(changeInVelocity2);
		}

		/*if (aabb1.IsCollidingWith(aabb2))
		{
			Transform& transform1 = *gameObject->GetComponent<Transform>();
			Transform& transform2 = *boxCollider.gameObject->GetComponent<Transform>();

			Vec3 position1 = transform1.GetPosition();
			Vec3 position2 = transform2.GetPosition();

			Vec3 min1 = this->GetAABB().GetMin();
			Vec3 max1 = this->GetAABB().GetMax();
			Vec3 min2 = boxCollider.GetAABB().GetMin();
			Vec3 max2 = boxCollider.GetAABB().GetMax();

			float displacementX1 = (position1.x + max1.x) - (position2.x + min1.x);
			PG_TRACE(displacementX1);

			Vec3 displacement = transform2.GetPosition() - transform1.GetPosition();
			Vec3 relativeVelocity = rigidBody2.GetVelocity() - rigidBody1.GetVelocity();
			float movingTowards = Maths::DotProduct(relativeVelocity, displacement);

			if (movingTowards < 0.0f)
			{
				float x = abs(displacement.x) > abs(displacement.y) && abs(displacement.x) > abs(displacement.z) ? displacement.x > 0 ? 1.0f : -1.0f : 0.0f;
				float y = x == 0.0f && abs(displacement.y) > abs(displacement.x) && abs(displacement.y) > abs(displacement.z) ? displacement.y > 0 ? 1.0f : -1.0f : 0.0f;
				float z = y == 0.0f && abs(displacement.z) > abs(displacement.x) && abs(displacement.z) > abs(displacement.y) ? displacement.z > 0 ? 1.0f : -1.0f : 0.0f;
				Vec3 collisionNormal(x, y, z);

				float dotProduct = Maths::DotProduct(relativeVelocity, collisionNormal);
				float restitution = 1.0f;
				float impulseScalar = -(1 + restitution) * dotProduct;
				impulseScalar /= 1.0f / rigidBody1.GetMass() + 1.0f / rigidBody2.GetMass();
				Vec3 impulse = impulseScalar * collisionNormal;

				rigidBody1.AddVelocity(-1.0f / rigidBody1.GetMass() * impulse);
				rigidBody2.AddVelocity(1.0f / rigidBody2.GetMass() * impulse);
			}
		}*/
	}

	AABB<3> BoxCollider::GetAABB() const
    {
        return aabb;
    }

	AABB<3> BoxCollider::GetTransformedAABB(const Transform& transform) const
	{
		Vec3 min(transform.GetPosition());
		min.x -= aabb.GetSize()[0];		
		min.y -= aabb.GetSize()[1];		
		min.z -= aabb.GetSize()[2];		

		Vec3 max(transform.GetPosition());
		max.x += aabb.GetSize()[0];
		max.y += aabb.GetSize()[1];
		max.z += aabb.GetSize()[2];

		return AABB<3>(min, max);
	}

	std::string BoxCollider::GetComponentName() const
	{
		return ComponentName();
	}
}