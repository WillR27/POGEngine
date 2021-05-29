#pragma once

#include "Common.h"

namespace POG::Core
{
	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
		virtual void OnEntityDestroyed(EntityId entityId) = 0;
	};

	template <typename T>
	class ComponentArray : public IComponentArray
	{
	public:
		ComponentArray()
			: components()
			, entityIds()
		{
		}

		T& GetComponent(EntityId entityId)
		{
			// Find the index of the entity
			EntityId index;
			if (!entityIds.Find(entityId, index))
			{
				POG_ASSERT(false, "No component exists for entity id: {0}.", entityId);
			}

			// If it exists return the corresponding component
			return components[index];
		}

		template <typename T>
		void SetComponent(EntityId entityId, T component)
		{
			// Find the index of the entity
			EntityId index;
			if (!entityIds.Find(entityId, index))
			{
				POG_ASSERT(false, "No component exists for entity id: {0}.", entityId);
			}

			// If it exists set the component
			components[index] = component;
		}

		T& AddComponent(EntityId entityId, const T& component)
		{
			// Get the count before adding the new entity id
			EntityId count = entityIds.Count();

			// Add the new entity id to the list
			entityIds.Insert(entityId);

			// Now add the component to the components at the same index
			components[count] = component;

			// Return a reference to the copied component
			return components[count];
		}

		void RemoveComponent(EntityId entityId)
		{
			// Find the index of the entity
			EntityId indexOfRemovedElement;
			if (!entityIds.Find(entityId, indexOfRemovedElement))
			{
				POG_ASSERT(false, "No component exists for entity id: {0}.", entityId);
			}

			// Remove the entity id from the sparse set
			entityIds.Remove(entityId);

			// Count after removing to get the index of the last element
			EntityId indexOfLastElement = entityIds.Count();

			// Move the last component to the location of the removed component
			components[indexOfRemovedElement] = components[indexOfLastElement];
		}

		virtual void OnEntityDestroyed(EntityId entityId) override
		{
			// Remove the component if it exists
			if (entityIds.Contains(entityId))
			{
				RemoveComponent(entityId);
			}
		}

	private:
		// A packed array containing the components
		std::array<T, MaxEntities> components;

		// A sparse set in the same order as the components array
		SparseSet<EntityId, MaxEntities, MaxEntityId> entityIds;
	};

	class ComponentManager
	{
	public:
		template <typename T>
		void RegisterComponent()
		{
			// Get the hash id for this component
			static const Common::HashId hashId = Common::Hash<T, Common::HashId>();

			// Check the component doesn't already exist
			POG_ASSERT(componentTypeIds.find(hashId) == componentTypeIds.end(), "Tried to register a component that already exists: {0}.", STRINGIFY(T));

			// Insert the component hash id to the map
			componentTypeIds[hashId] = count;

			// Create the empty component array
			ComponentArray<T>* componentArray = new ComponentArray<T>();
			componentArrays[count] = std::shared_ptr<IComponentArray>(static_cast<IComponentArray*>(componentArray));

			count++;
		}

		template <typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray()
		{
			// Get the hash id for this component
			static const Common::HashId hashId = Common::Hash<T, Common::HashId>();

			// Find the corresponding component id index
			POG_ASSERT(componentTypeIds.find(hashId) != componentTypeIds.end(), "Tried to access a component array that didn't exist: {0}.", STRINGIFY(T));

			ComponentTypeId asd = componentTypeIds[hashId];

			auto asdsada = componentArrays[asd];

			// Return the component array at this index
			return std::static_pointer_cast<ComponentArray<T>>(componentArrays[componentTypeIds[hashId]]);
		}

		template <typename T>
		T& GetComponent(EntityId entityId)
		{
			return GetComponentArray<T>()->GetComponent(entityId);
		}

		template <typename T>
		void SetComponent(EntityId entityId, T component)
		{
			GetComponentArray<T>()->SetComponent(entityId, component);
		}

		template <typename T>
		T& AddComponent(EntityId entityId, const T& component)
		{
			return GetComponentArray<T>()->AddComponent(entityId, component);
		}

		template <typename T>
		void RemoveComponent(EntityId entityId)
		{
			GetComponentArray<T>()->RemoveComponent(entityId);
		}

		void OnEntityDestroyed(EntityId entityId)
		{
			for (int i = 0; i < count; i++)
			{
				componentArrays[i]->OnEntityDestroyed(entityId);
			}
		}

		template <typename T>
		ComponentTypeId GetComponentTypeId()
		{
			// Get the hash id for this component
			static const Common::HashId hashId = Common::Hash<T, Common::HashId>();

			return componentTypeIds[hashId];
		}

	private:
		// An array of component arrays
		std::array<std::shared_ptr<IComponentArray>, MaxComponentTypes> componentArrays;

		// Sparse set containing the indexes of each component array for each type of component
		std::unordered_map<Common::HashId, ComponentTypeId> componentTypeIds;

		// Count of component arrays
		ComponentTypeId count = 0;
	};
}