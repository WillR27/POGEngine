#include "pgepch.h"
#include "BoxCollider.h"

#include "RigidBody.h"
#include <Game\GameObject\Components\MeshRenderer.h>

namespace PEngine
{
    BoxCollider::BoxCollider(std::initializer_list<float> dimensions)
        : aabb(dimensions)
    {
    }

	void BoxCollider::CollideWith(BoxCollider& boxCollider)
	{
		RigidBody* rigidBody1 = this->To<RigidBody>();
		PG_ASSERT(rigidBody1, GetName() + " has a box collider component but no rigid body component!");

		RigidBody* rigidBody2 = boxCollider.To<RigidBody>();
		PG_ASSERT(rigidBody2, boxCollider.GetName() + " has a box collider component but no rigid body component!");

		const AABB<3>& aabb1 = GetTransformedAABB();
		const AABB<3>& aabb2 = boxCollider.GetTransformedAABB();

		if (aabb1.IsCollidingWith(aabb2))
		{
			Transform* transform1 = this->To<Transform>();
			Transform* transform2 = boxCollider.To<Transform>();

			MeshRenderer* mr1 = this->To<MeshRenderer>();
			MeshRenderer* mr2 = boxCollider.To<MeshRenderer>();

			Vec3 displacement = transform2->GetPosition() - transform1->GetPosition();
			Vec3 relativeVelocity = rigidBody2->GetVelocity() - rigidBody1->GetVelocity();
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
				impulseScalar /= 1.0f / rigidBody1->GetMass() + 1.0f / rigidBody2->GetMass();
				Vec3 impulse = impulseScalar * collisionNormal;

				rigidBody1->AddVelocity(-1.0f / rigidBody1->GetMass() * impulse);
				rigidBody2->AddVelocity(1.0f / rigidBody2->GetMass() * impulse);
			}
		}
	}

	AABB<3> BoxCollider::GetAABB() const
    {
        return aabb;
    }

	AABB<3> BoxCollider::GetTransformedAABB() const
	{
		const Transform* transform = this->To<Transform>();
		PG_ASSERT((transform != nullptr), GetName() + " has a box collider component but no transform component!");

		Vec3 min(transform->GetPosition());
		min.x -= aabb.GetSize()[0];		
		min.y -= aabb.GetSize()[1];		
		min.z -= aabb.GetSize()[2];		

		Vec3 max(transform->GetPosition());
		max.x += aabb.GetSize()[0];
		max.y += aabb.GetSize()[1];
		max.z += aabb.GetSize()[2];

		return AABB<3>(min, max);
	}
}