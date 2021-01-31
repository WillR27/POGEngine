#include "pgpch.h"
#include "World.h"

namespace Pagoog
{
	int World::ChunkRadius = 2;
	int World::TotalChunks = World::ChunkRadius * World::ChunkRadius * World::ChunkRadius;
}