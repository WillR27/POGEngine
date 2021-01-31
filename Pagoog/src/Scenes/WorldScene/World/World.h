#pragma once

namespace Pagoog
{
	class World
	{
	public:
		// The number of chunks to load in each direction, e.g. 4 would be 9x9x9 chunks.
		static int ChunkRadius;

		// The total number of chunks that should be loaded in the world.
		static int TotalChunks;
	};
}

