#include "ExamplePCH.h"
#include "Bullet.h"

using namespace POG;

namespace Example
{
	Bullet::Bullet(Core::EntityInfo entityInfo, Core::ECSManager& ecsManager, Maths::Vec3 origin, float direction)
		: Entity::Entity(entityInfo, ecsManager)
	{
		AddComponent(BulletInfo
			{
				.timeExisted = 0.0f,
			});

		AddComponent(Core::Sprite
			{
				.texture = &Core::TextureManager::GetGlobalTexture("Bullet"),
			});

		AddComponent(Core::Transform
			{
				.position = origin,
				.orientation = Maths::Quat(Maths::Vec3(0.0f, 0.0f, -direction)),
				.scale = Maths::Vec3(1.0f, 1.0f, 1.0f),
			});
	}

	POG::Core::Signature BulletMoveSystem::GetSignature(POG::Core::ECSManager& ecsManager)
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
}