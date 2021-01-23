#pragma once

#include "ECS/ECS.h"

namespace PEngine
{
	class Player
	{
	public:
		Player() = default;
		~Player() = default;

		static Entity Create(ECSManager& ecsManager);
	private:

	};
}

