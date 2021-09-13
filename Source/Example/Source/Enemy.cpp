#include "ExamplePCH.h"
#include "Enemy.h"

#include "Player.h"

using namespace POG;

namespace Example
{
	Enemy::Enemy(Core::EntityInfo entityInfo, Core::ECSManager& ecsManager, Maths::Vec3 origin)
		: Entity::Entity(entityInfo, ecsManager)
	{
		AddComponent(EnemyInfo
			{
			});

		AddComponent(Core::BoxCollider2D
			{
			});

		AddComponent(Core::Sprite
			{
				.texture = &Core::TextureManager::GetGlobalTexture("Enemy"),
			});

		AddComponent(Core::Transform
			{
				.position = origin,
			});

		AddComponent(Core::Interpolator
			{
			});
	}

	Core::Signature EnemySystem::GetSignature(POG::Core::ECSManager& ecsManager)
	{
		Core::Signature signature;
		signature.set(ecsManager.GetComponentTypeId<EnemyInfo>());
		return signature;
	}

	void EnemySystem::Update(float dt)
	{
		auto& playerTransform = player.GetComponent<Core::Transform>();

		if (timeSinceLastSpawn > 5.0f)
		{
			if (entityIds.size() < 5)
			{
				ecsManager.CreateEntity<Enemy>(playerTransform.position);

				timeSinceLastSpawn = 0.0f;
			}
		}
		else
		{
			timeSinceLastSpawn += dt;
		}
	}
}