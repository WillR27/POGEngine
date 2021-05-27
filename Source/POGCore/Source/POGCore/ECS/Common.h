#pragma once

#include "POGCommon.h"
#include "POGDebug.h"
#include "POGLog.h"

#include <array>
#include <bitset>
#include <cstdint>
#include <limits>
#include <memory>
#include <queue>
#include <set>
#include <unordered_map>

namespace POG::Core
{
	using EntityId = std::uint16_t;
	const EntityId MaxEntities = 10000; //std::numeric_limits<Entity>::max() - 1;
	const EntityId MaxEntityId = MaxEntities - 1;
	using EntityVersion = std::uint16_t;

	using ComponentTypeId = std::uint8_t;
	const ComponentTypeId MaxComponentTypes = std::numeric_limits<ComponentTypeId>::max();
	using Signature = std::bitset<MaxComponentTypes>;

	struct EntityInfo
	{
		EntityId id;
		EntityVersion version;
	};
}