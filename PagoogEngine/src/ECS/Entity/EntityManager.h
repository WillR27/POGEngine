#pragma once

#include <queue>

#include "Debug/Debug.h"
#include "ECS/ECS.h"

namespace PEngine
{
	class EntityManager
	{
	public:
		EntityManager()
			: availableEntities()
			, signatures()
			, livingEntityCount(0)
		{
			// Initialise the queue of all possible entity IDs
			for (Entity entity = 1; entity < MaxEntities; entity++)
			{
				availableEntities.push(entity);
			}
		}

		Entity CreateEntity()
		{
			PG_ASSERT(livingEntityCount < MaxEntities, "Too many entities ({0}/{1}) in existence to create a new one!", livingEntityCount, MaxEntities);

			// Take the next ID from the front of the queue
			Entity entity = availableEntities.front();
			availableEntities.pop();
			livingEntityCount++;

			return entity;
		}

		void DestroyEntity(Entity entity)
		{
			PG_ASSERT(entity < MaxEntities, "Tried to destroy entity ({0}) out of range ({1})!", entity, MaxEntities);

			// Reset the signature for the given entity
			signatures[entity].reset();

			// Add the entity's ID to the back of the queue
			availableEntities.push(entity);
			livingEntityCount--;
		}

		Signature GetSignature(Entity entity)
		{
			PG_ASSERT(entity < MaxEntities, "Tried to access entity ({0}) out of range ({1})!", entity, MaxEntities);

			// Get the given entity's signature
			return signatures[entity];
		}

		void SetSignature(Entity entity, Signature signature)
		{
			PG_ASSERT(entity < MaxEntities, "Tried to access entity ({0}) out of range ({1})!", entity, MaxEntities);

			// Set the given entity's signature
			signatures[entity] = signature;
		}

	private:
		// Queue of unused entity IDs
		std::queue<Entity> availableEntities;

		// Array of signatures for each entity ID
		std::array<Signature, MaxEntities> signatures;

		// Number of living entities
		Entity livingEntityCount;
	};
}

