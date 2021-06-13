#pragma once

#include "POGCore.h"
#include "POGMaths.h"

namespace Example
{
	class Player;

	struct EnemyInfo
	{

	};

	class Enemy : public POG::Core::Entity
	{
	public:
		Enemy() = default;
		Enemy(POG::Core::EntityInfo entityInfo, POG::Core::ECSManager& ecsManager, POG::Maths::Vec3 origin);

		~Enemy() = default;
	};

	class EnemySystem : public POG::Core::System
	{
	public:
		EnemySystem(POG::Core::ECSManager& ecsManager, Player& player)
			: System::System(ecsManager)
			, player(player)
			, timeSinceLastSpawn(0.0f)
		{
		}

		static POG::Core::Signature GetSignature(POG::Core::ECSManager& ecsManager);

		void Update(float dt);

	private:
		Player& player;

		float timeSinceLastSpawn;
	};
}

