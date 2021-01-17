#pragma once

#include <unordered_map>

#include "Debug/Debug.h"
#include "ECS/ECS.h"

namespace PEngine
{
	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
		virtual void EntityDestroyed(Entity entity) = 0;
	};

	// T is the component type
	template <typename T>
	class ComponentArray : public IComponentArray
	{
	public:
		ComponentArray()
			: componentArray()
			, entityToIndexMap()
			, indexToEntityMap()
			, count(0)
		{
		}

		void InsertData(Entity entity, T component)
		{
			PG_ASSERT(entityToIndexMap.find(entity) == entityToIndexMap.end(), "Added component to entity \"{0}\" that already existed!", entity);

			// Add the new entry at the end of the array
			Entity index = count;
			entityToIndexMap[entity] = index;
			indexToEntityMap[index] = entity;
			componentArray[index] = component;
			count++;
		}

		void RemoveData(Entity entity)
		{
			PG_ASSERT(entityToIndexMap.find(entity) != entityToIndexMap.end(), "Removed component from entity \"{0}\" that did not exist!", entity);

			// Copy the element at the end to the removed entity's index
			Entity indexOfRemovedEntity = entityToIndexMap[entity];
			Entity indexOfLastElement = count - 1;
			componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

			// Update maps
			Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
			entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
			indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

			count--;
		}

		T& GetComponent(Entity entity)
		{
			PG_ASSERT(entityToIndexMap.find(entity) != entityToIndexMap.end(), "Retrieving component for entity \"{0}\" that does not exists");

			return componentArray[entityToIndexMap[entity]];
		}

		void EntityDestroyed(Entity entity)
		{
			if (entityToIndexMap.find(entity) != entityToIndexMap.end())
			{
				RemoveData(entity);
			}
		}

	private:
		// The packed array of components of type T
		std::array<T, MaxEntities> componentArray;

		// Map from entity ID to index of component in array
		std::unordered_map<Entity, Entity> entityToIndexMap;

		// Map from index of component in array to entity ID
		std::unordered_map<Entity, Entity> indexToEntityMap;

		// The number of components currently in the array
		Entity count;
	};
}