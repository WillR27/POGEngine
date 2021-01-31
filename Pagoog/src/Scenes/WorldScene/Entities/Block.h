#pragma once

#include "ECS/ECS.h"

namespace Pagoog
{
	class Block : public Entity
	{
	public:
		Block() = default;
		Block(EntityInfo entityInfo, ECSManager& ecsManager);
		~Block() = default;

	private:

	};
}

