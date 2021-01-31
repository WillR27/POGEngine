#include "pgpch.h"
#include "Chunk.h"

#include "Render/Mesh/Mesh.h"
#include "Render/Mesh/MeshDataTypes.h"
#include "Render/Mesh/Primitives/Plane.h"
#include "Render/Mesh/Primitives/Primitives.h"
#include "Scene/Scene.h"

namespace Pagoog
{
	int Chunk::Size = 2;
	int Chunk::TotalBlocks = Chunk::Size * Chunk::Size * Chunk::Size;

	Chunk::Chunk(PEngine::EntityInfo entityInfo, PEngine::ECSManager& ecsManager, int chunkX, int chunkY, int chunkZ)
		: Entity::Entity(entityInfo, ecsManager)
	{
		AddComponent(ChunkInfo
			{
				.chunkX = chunkX,
				.chunkY = chunkY,
				.chunkZ = chunkZ,

				.blockIds = nullptr
			});

		AddComponent(Transform
			{
				.position = Vec3(0.0f, 0.0f, 0.0f),
				.orientation = Quat(Vec3(0.0f, 0.0f, 0.0f)),
				.scale = Vec3(1.0f, 1.0f, 1.0f),

				.prevPosition = Vec3(0.0f, 0.0f, 0.0f),
				.prevOrientation = Quat(Vec3(0.0f, 0.0f, 0.0f)),
				.prevScale = Vec3(1.0f, 1.0f, 1.0f)
			});

		AddComponent(MeshRenderer
			{
				.mesh = nullptr,
				.material = nullptr
			});
	}

	ChunkSystem::ChunkSystem(ECSManager& ecsManager, Player& player)
		: System::System(ecsManager)
		, player(player)
		, prevPlayerChunkX(0)
		, prevPlayerChunkY(0)
		, prevPlayerChunkZ(0)
	{
	}

	Signature ChunkSystem::GetSignature(ECSManager& ecsManager)
	{
		Signature signature;
		signature.set(ecsManager.GetComponentTypeId<ChunkInfo>());
		signature.set(ecsManager.GetComponentTypeId<Transform>());
		signature.set(ecsManager.GetComponentTypeId<MeshRenderer>());
		return signature;
	}

	void ChunkSystem::Update()
	{
		auto& playerTransform = player.GetComponent<Transform>();
		
		int playerX = 0;
		int playerY = 0 - 20;
		int playerZ = 0;

		int playerChunkX = playerX / Chunk::Size;
		int playerChunkY = playerY / Chunk::Size;
		int playerChunkZ = playerZ / Chunk::Size;

		int minChunkX = playerChunkX - World::ChunkRadius;
		int minChunkY = playerChunkY - World::ChunkRadius;
		int minChunkZ = playerChunkZ - World::ChunkRadius;

		int maxChunkX = playerChunkX + World::ChunkRadius;
		int maxChunkY = playerChunkY + World::ChunkRadius;
		int maxChunkZ = playerChunkZ + World::ChunkRadius;

		// Used to store the chunk ids to remove this tick
		std::vector<EntityId> chunksIdsToDestroy;

		// Work out which chunks should no longer exist
		for (EntityId chunkId : entityIds)
		{
			auto& chunkInfo = ecsManager.GetComponent<ChunkInfo>(chunkId);

			if (chunkInfo.chunkX < minChunkX || chunkInfo.chunkX > maxChunkX ||
				chunkInfo.chunkY < minChunkY || chunkInfo.chunkY > maxChunkY ||
				chunkInfo.chunkZ < minChunkZ || chunkInfo.chunkZ > maxChunkZ)
			{
				chunksIdsToDestroy.push_back(chunkId);
			}
		}

		// TODO: Use the player's prev position to work out new chunks that need generating
		// Work out the new chunks that need generating
		for (int x = minChunkX; x <= maxChunkX; x++)
		{
			for (int y = minChunkY; y <= maxChunkY; y++)
			{
				for (int z = minChunkZ; z <= maxChunkZ; z++)
				{
					bool chunkAlreadyExists = false;

					for (EntityId chunkId : entityIds)
					{
						auto& chunkInfo = ecsManager.GetComponent<ChunkInfo>(chunkId);

						if (x == chunkInfo.chunkX && y == chunkInfo.chunkY && z == chunkInfo.chunkZ)
						{
							chunkAlreadyExists = true;
							break;
						}
					}

					if (!chunkAlreadyExists)
					{
						GenerateChunk(x, y, z);
					}
				}
			}
		}

		for (EntityId chunkIdToDestroy : chunksIdsToDestroy)
		{
			auto& chunkInfo = ecsManager.GetComponent<ChunkInfo>(chunkIdToDestroy);

			// Make sure we delete the heap allocated block ids
			delete[] chunkInfo.blockIds;

			// Then destroy the chunk completely
			ecsManager.DestroyEntity(chunkIdToDestroy);
		}

		prevPlayerChunkX = playerChunkX;
		prevPlayerChunkY = playerChunkY;
		prevPlayerChunkZ = playerChunkZ;
	}

	void ChunkSystem::GenerateChunk(int chunkX, int chunkY, int chunkZ)
	{
		// Create a new chunk
		Chunk& chunk = ecsManager.CreateEntity<Chunk>(chunkX, chunkY, chunkZ);

		// Work out the actual coords of the chunk
		float x = chunkX * Chunk::Size;
		float y = chunkY * Chunk::Size;
		float z = chunkZ * Chunk::Size;

		// Get the transform component of the chunk
		auto& transform = chunk.GetComponent<Transform>();

		// Set the location of the chunk
		transform.position.x = x;
		transform.position.y = y;
		transform.position.z = z;

		//GenerateBlocks(chunk);
		GenerateMesh(chunk);
	}

	void ChunkSystem::GenerateBlocks(Chunk& chunk)
	{
		auto& chunkInfo = chunk.GetComponent<ChunkInfo>();

		// Create a new array to contain the block ids for the chunk
		chunkInfo.blockIds = new int[Chunk::TotalBlocks];

		for (int x = 0; x < Chunk::Size; x++)
		{
			// The pointer to the start of each x location
			int* startX = chunkInfo.blockIds + (x * Chunk::Size * Chunk::Size);

			for (int y = 0; y < Chunk::Size; y++)
			{
				// The pointer to the start of each y location
				int* startY = startX + (y * Chunk::Size);

				for (int z = 0; z < Chunk::Size; z++)
				{
					// Set the block id
					startY[z] = 0;
				}
			}
		}
	}

	void ChunkSystem::GenerateMesh(Chunk& chunk)
	{
		auto& chunkInfo = chunk.GetComponent<ChunkInfo>();

		Shared<Mesh> mesh = MakeShared<Mesh>();

		std::vector<Vertex::Position::ValueType> tempVertexPositions;
		std::vector<Vertex::Colour::ValueType> tempVertexColours;
		std::vector<Vertex::Index::ValueType> tempVertexIndices;
		int total = 0;
		for (int x = 0; x < Chunk::Size; x++)
		{
			for (int y = 0; y < Chunk::Size; y++)
			{
				for (int z = 0; z < Chunk::Size; z++)
				{
					for (int dir = Plane::Direction::First; dir != Plane::Direction::Last; dir++)
					{
						Plane::Direction direction = static_cast<Plane::Direction>(dir);
						auto positions	= Plane::GetPositions(direction);
						auto colours	= Plane::GetColours();
						auto indices	= Plane::GetIndices(direction);

						for (int i = 0; i < positions.size() / Vertex::Position::Count; i++)
						{
							positions[i * Vertex::Position::Count] = positions[i * Vertex::Position::Count] + x;
							positions[i * Vertex::Position::Count + 1] = positions[i * Vertex::Position::Count + 1] + y;
							positions[i * Vertex::Position::Count + 2] = positions[i * Vertex::Position::Count + 2] + z;
						}

						int currentSize = tempVertexIndices.size();
						for (auto& it = indices.begin(); it != indices.end(); it++)
						{
							(*it) = (*it) + 4 * total;
						}

						tempVertexPositions.insert(tempVertexPositions.end(), positions.begin(), positions.end());
						tempVertexColours.insert(tempVertexColours.end(), colours.begin(), colours.end());
						tempVertexIndices.insert(tempVertexIndices.end(), indices.begin(), indices.end());
						total++;
					}
				}
			}
		}

 		mesh->SetPositionData(&tempVertexPositions[0], tempVertexPositions.size() * sizeof(Vertex::Position::ValueType));
		mesh->SetColourData(&tempVertexColours[0], tempVertexColours.size() * sizeof(Vertex::Colour::ValueType));
		mesh->SetIndexData(&tempVertexIndices[0], tempVertexIndices.size() * sizeof(Vertex::Index::ValueType));
		mesh->Build();

		auto& meshRenderer = chunk.GetComponent<MeshRenderer>();
		meshRenderer.mesh = mesh;
		meshRenderer.material = ecsManager.GetScene().GetMaterialManager().FindMaterial("Material1");
	}
}