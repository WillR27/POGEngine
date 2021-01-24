#pragma once

#include "ECS/ECS.h"
#include "Input/InputPackage.h"

namespace Pagoog
{
	class Player : public PEngine::Entity
	{
	public:
		Player() = default;
		Player(PEngine::EntityInfo entityInfo, PEngine::ECSManager& ecsManager, float moveSpeed, float sprintMultiplier, float lookSpeed);
		~Player() = default;

		virtual void OnCreate() override;

		void InputCallback(PEngine::InputPackage& inputPackage, float dt);

	private:
		float moveSpeed;
		float sprintMultiplier;
		float lookSpeed;
	};
}