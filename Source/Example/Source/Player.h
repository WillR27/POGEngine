#pragma once

#include "POGCore.h"

namespace Example
{
	class Player : POG::Core::Entity
	{
	public:
		Player() = default;
		Player(POG::Core::EntityInfo entityInfo, POG::Core::ECSManager& ecsManager, float moveSpeed, float sprintMultiplier);

		~Player() = default;

		void InputCallback(POG::Core::InputPackage& inputPackage, float dt);

	private:
		float moveSpeed;
		float sprintMultiplier;
	};
}