#include "ExamplePCH.h"
#include "Bullet.h"

#include "POGCore/Physics/Collisions.h"

using namespace POG;

namespace Example
{
	Bullet::Bullet(Core::EntityInfo entityInfo, Core::ECSManager& ecsManager, Maths::Vec3 origin, float direction)
		: Entity::Entity(entityInfo, ecsManager)
	{
		AddComponent(BulletInfo
			{
			});

		AddComponent(Core::BoxCollider2D
			{
				.min = Maths::Vec2(-0.05f, -0.05f),
				.max = Maths::Vec2(0.05f, 0.05f),
			});

		AddComponent(Core::Sprite
			{
				.texture = &Core::TextureManager::GetGlobalTexture("Bullet"),
			});

		AddComponent(Core::Transform
			{
				.position = origin,
				.orientation = Maths::Quat(Maths::Vec3(0.0f, 0.0f, -direction)),
			});

		AddComponent(Core::Interpolator
			{
			});
	}

	Core::Signature BulletMoveSystem::GetSignature(Core::ECSManager& ecsManager)
	{
		Core::Signature signature;
		signature.set(ecsManager.GetComponentTypeId<BulletInfo>());
		return signature;
	}

	void BulletMoveSystem::Update(float dt)
	{
		std::vector<Core::EntityId> bulletsToDestroy;

		for (auto bulletId : entityIds)
		{
			auto& bulletInfo = ecsManager.GetComponent<BulletInfo>(bulletId);
			bulletInfo.timeExisted += dt;

			if (bulletInfo.timeExisted > 3.0f)
			{
				bulletsToDestroy.push_back(bulletId);
				continue;
			}

			auto& bulletTransform = ecsManager.GetComponent<Core::Transform>(bulletId);

			bulletTransform.position += (Maths::ToRightVec(bulletTransform.orientation) * dt);
		}

		for (auto bulletId : bulletsToDestroy)
		{
			ecsManager.DestroyEntity(bulletId);
		}
	}

	Core::Signature BulletEnemyCollisionSystem::GetSignature(Core::ECSManager& ecsManager)
	{
		Core::Signature signature;
		signature.set(ecsManager.GetComponentTypeId<EnemyInfo>());
		return signature;
	}

	void BulletEnemyCollisionSystem::Update(Core::EntityId bulletId, float dt)
	{
		Core::Transform& transform1 = ecsManager.GetComponent<Core::Transform>(bulletId);
		Core::BoxCollider2D& boxCollider1 = ecsManager.GetComponent<Core::BoxCollider2D>(bulletId);

		for (auto enemyId : entityIds)
		{
			Core::Transform& transform2 = ecsManager.GetComponent<Core::Transform>(enemyId);
			Core::BoxCollider2D& boxCollider2 = ecsManager.GetComponent<Core::BoxCollider2D>(enemyId);

			Core::CollisionResult result = Core::TestCollisionBoxCollider2D(transform1, boxCollider1, transform2, boxCollider2);

			if (result.collision)
			{
				POG_WARN("hit");
				transform1.position += result.displacement;
			}
		}
	}

	Core::Signature BulletCollisionSystem::GetSignature(Core::ECSManager& ecsManager)
	{
		Core::Signature signature;
		signature.set(ecsManager.GetComponentTypeId<BulletInfo>());
		return signature;
	}

	void BulletCollisionSystem::Update(float dt)
	{
		for (auto bulletId : entityIds)
		{
			bulletEnemyCollisionSystem.Update(bulletId, dt);
		}
	}
}