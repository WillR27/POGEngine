#pragma once

#include "Common.h"

namespace POG::Core
{
	class System;

	class EntityManager
	{
	public:
		void Init()
		{
			for (EntityId i = 0; i < MaxEntities; i++)
			{
				// Add all possible ids to the queue
				availableEntityIds.push(i);

				// Set all entity versions to start at 1
				currentEntityVersions[i] = 1;
			}
		}

		EntityInfo Create()
		{
			// Get the entity id at the front of the queue
			EntityId entityId = availableEntityIds.front();
			availableEntityIds.pop();

			// Return an entity struct containing the entity id and the version of that entity
			return { entityId, currentEntityVersions[entityId] };
		}

		void Destroy(EntityId entityId)
		{
			// Add this entity id back to the queue of available entity ids
			availableEntityIds.push(entityId);

			// Increment the version for this entity id
			currentEntityVersions[entityId]++;

			// Reset the signature for this entity
			entitySignatures[entityId].reset();
		}

		EntityVersion GetVersion(EntityId entityId) const
		{
			return currentEntityVersions[entityId];
		}

		bool IsEntityValid(EntityInfo entityInfo) const
		{
			return entityInfo.version == GetVersion(entityInfo.id);
		}

		Signature GetEntitySignature(EntityId entityId)
		{
			return entitySignatures[entityId];
		}

		void SetEntitySignature(EntityId entityId, Signature newSignature)
		{
			entitySignatures[entityId] = newSignature;
		}

		template <typename T>
		void OnSystemRegistered(std::shared_ptr<T> system)
		{
			// Check if any entities' signature match
			for (int i = 0; i < MaxEntities; i++)
			{
				Signature entitySignature = entitySignatures[i];
				Signature systemSignature = T::GetSignature();

				// If the signatures match, add the entity id
				if ((systemSignature & entitySignature) == systemSignature)
				{
					system->entityIds.insert(i);
				}
			}
		}

	private:
		// Currently available entity ids
		std::queue<EntityId> availableEntityIds;

		// Current versions for each entity id
		std::array<EntityVersion, MaxEntities> currentEntityVersions;

		// Current entity signatures
		std::array<Signature, MaxEntities> entitySignatures;
	};
}