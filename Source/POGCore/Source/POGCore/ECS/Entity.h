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
			// Start at 1 so we can use 0 as a null entity id
			for (EntityId i = 1; i < MaxEntities; i++)
			{
				// Add all possible ids to the queue
				availableEntityIds.push(i);

				// Set all entity versions to start at 0
				currentEntityVersions[i] = 0;
			}
		}

		EntityInfo Create()
		{
			// Get the entity id at the front of the queue
			EntityId entityId = availableEntityIds.front();
			availableEntityIds.pop();
			usedEntityIds.push_back(entityId);

			std::stringstream ss;
			ss << "Entity " << entityId;
			entityNames[entityId] = ss.str();

			// Return an entity struct containing the entity id and the version of that entity
			return { entityId, currentEntityVersions[entityId] };
		}

		void Destroy(EntityId entityId)
		{
			// Add this entity id back to the queue of available entity ids
			availableEntityIds.push(entityId);

			// Remove the entity id from the vector of used ids
			auto it = std::find(usedEntityIds.begin(), usedEntityIds.end(), entityId);
			if (it != usedEntityIds.end())
			{
				usedEntityIds.erase(it);
			}

			// Increment the version for this entity id
			currentEntityVersions[entityId]++;

			// Reset the signature for this entity
			entitySignatures[entityId].reset();

			// Reset the entity's name
			entityNames[entityId] = "ENTITY NAME ERROR";

			// Destroy any children this entity had
			std::vector<EntityId>& children = entityChildren[entityId];
			while (!children.empty())
			{
				Destroy(children[0]);
			}

			// Get the parent id
			EntityId parentId = entityParents[entityId];

			// Remove the entity from the parent's children if it had a parent
			std::vector<EntityId>& parentsChildren = entityChildren[parentId];
			auto it2 = std::find(parentsChildren.begin(), parentsChildren.end(), entityId);
			if (it2 != parentsChildren.end())
			{
				parentsChildren.erase(it2);
			}

			// Clear the entity's parent
			entityParents[entityId] = NullEntity;
		}

		std::string GetName(EntityId entityId) const
		{
			return entityNames[entityId];
		}

		void SetName(EntityId entityId, std::string name)
		{
			entityNames[entityId] = name;
		}

		std::vector<EntityId> GetChildren(EntityId entityId) const
		{
			return entityChildren[entityId];
		}

		bool HasChildren(EntityId entityId) const
		{
			return GetChildren(entityId).size() != 0;
		}

		EntityId GetParent(EntityId entityId) const
		{
			return entityParents[entityId];
		}

		bool HasParent(EntityId entityId) const
		{
			return GetParent(entityId) != NullEntity;
		}

		void SetParent(EntityId entityId, EntityId parentId)
		{
			// Make sure the new parent is not a child of the entity
			for (EntityId childId : entityChildren[entityId])
			{
				POG_ASSERT(childId != parentId, "Cannot set entity's parent to one of its children!");
			}

			EntityId oldParentId = entityParents[entityId];

			// Set the new parent and append the entity as a child of the parent
			entityParents[entityId] = parentId;
			entityChildren[parentId].push_back(entityId);

			// Remove the entity from the old parent's children if it had a parent
			std::vector<EntityId>& oldParentsChildren = entityChildren[oldParentId];
			auto it = std::find(oldParentsChildren.begin(), oldParentsChildren.end(), entityId);
			if (it != oldParentsChildren.end())
			{
				oldParentsChildren.erase(it);
			}
		}

		std::vector<EntityId> GetUsedEntityIds() const
		{
			return usedEntityIds;
		}

		bool IsUsed(EntityId entityId) const
		{
			return std::find(usedEntityIds.begin(), usedEntityIds.end(), entityId) != usedEntityIds.end();
		}

		EntityVersion GetVersion(EntityId entityId) const
		{
			return currentEntityVersions[entityId];
		}

		bool IsValid(EntityInfo entityInfo) const
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

		// Currently used entity ids
		std::vector<EntityId> usedEntityIds;

		// Current versions for each entity id
		std::array<EntityVersion, MaxEntities> currentEntityVersions;

		// Current entity signatures
		std::array<Signature, MaxEntities> entitySignatures;

		// Names for each entity
		std::array<std::string, MaxEntities> entityNames;

		// Parents for each entity id
		std::array<EntityId, MaxEntities> entityParents;

		// Children for each entity id
		std::array<std::vector<EntityId>, MaxEntities> entityChildren;
	};
}