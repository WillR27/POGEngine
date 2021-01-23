#pragma once

#include "ECS/ECS.h"

namespace Pagoog
{
	class World
	{
	public:
		World(ECSManager& ecsManager);
		~World();

		void Init();

		void Update(float dt);

	private:
		ECSManager& ecsManager;
	};
}

