#pragma once

#include "ECS/ECS.h"

#include "Scenes/WorldScene/Entities/Player.h"
#include "Scenes/WorldScene/World/World.h"

namespace Pagoog
{
	struct ChunkInfo
	{
		int chunkX;
		int chunkY;
		int chunkZ;

		int* blockIds;
	};

	class Chunk : public Entity
	{
	public:
		// The dimensions of a chunk in blocks
		static int Size;
		// The total number of blocks per chunk
		static int TotalBlocks;

		Chunk() = default;
		Chunk(PEngine::EntityInfo entityInfo, PEngine::ECSManager& ecsManager, int chunkX, int chunkY, int chunkZ);
		~Chunk() = default;
	};

	class ChunkSystem : public System
	{
	public:
		ChunkSystem(ECSManager& ecsManager, Player& player);
		~ChunkSystem() = default;

		static Signature GetSignature(ECSManager& ecsManager);

		void Update();

	private:
		Player& player;

		int prevPlayerChunkX;
		int prevPlayerChunkY;
		int prevPlayerChunkZ;

		void GenerateChunk(int chunkX, int chunkY, int chunkZ);

		void GenerateBlocks(Chunk& chunk);
		void GenerateMesh(Chunk& chunk);
	};
}

