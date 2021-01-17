#pragma once

#include <set>

#include "ECS/ECS.h"

namespace PEngine
{
	class System
	{
	public:
		std::set<Entity> entities;
	};
}