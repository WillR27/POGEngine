#pragma once

#include <bitset>
#include <cstdint>
#include <limits>

namespace PEngine
{
	using Entity = std::uint32_t;
	const Entity MaxEntities = 10000; //std::numeric_limits<Entity>::max();

	using ComponentType = std::uint8_t;
	const ComponentType MaxComponents = std::numeric_limits<ComponentType>::max();
	
	using Signature = std::bitset<MaxComponents>;
}