#pragma once

#include "POGCore.h"
#include "POGGraphics.h"

#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"

namespace Example
{
	class ExampleScene : public POG::Core::Scene
	{
	public:
		ExampleScene() = default;

		virtual ~ExampleScene() = default;

		void Init() override;

		void Exit() override;

		void Input(POG::Core::InputPackage& inputPackage, float dt) override;
		void Update(float dt) override;
		void Frame(float alpha) override;

	private:
		Player player;
		POG::Core::Entity square;
		POG::Core::Entity child;

		std::shared_ptr<BulletMoveSystem> bulletMoveSystem;
		std::shared_ptr<BulletCollisionSystem> bulletCollisionSystem;
		std::shared_ptr<EnemySystem> enemySystem;

		bool flip;
	};
}

