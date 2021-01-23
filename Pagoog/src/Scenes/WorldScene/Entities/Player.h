#pragma once

#include "ECS/ECS.h"

namespace PEngine
{
	class Player : public Entity
	{
	public:
		Player() = default;
		Player(EntityInfo entityInfo, ECSManager& ecsManager);
		~Player() = default;

		virtual void OnCreate() override;
	private:

	};
}

