#pragma once

#include <bitset>
#include <cstdint>
#include <set>
#include <limits>
#include <queue>
#include <array>
#include <unordered_map>

#include "Core/Core.h"
#include "Debug/Debug.h"

#include "Components.h"

namespace PEngine
{
	template <typename T, T capacity, T maxValue>
	class SparseSet
	{
	public:
		SparseSet()
			: dense(nullptr)
			, sparse(nullptr)
			, count(0)
		{
			dense = new T[capacity];
			sparse = new T[maxValue + 1];

			for (T i = 0; i < capacity; i++)
			{
				dense[i] = 0;
			}

			for (T i = 0; i <= maxValue; i++)
			{
				sparse[i] = 0;
			}
		}

		~SparseSet()
		{
			delete[] sparse;
			delete[] dense;
		}

		bool Find(T element, T& index) const
		{
			// Get the index of the element
			index = sparse[element];

			// If the element in the dense array at the index matches, return true
			return index < count && dense[index] == element;
		}

		bool Contains(T element) const
		{
			T index;
			return Find(element, index);
		}

		T Insert(T element)
		{
			// Insert the element into the dense array at position count
			dense[count] = element;

			// Store the position of that element in the sparse array
			sparse[element] = count;

			// Finally increment count to match the current number of elements now stored in the dense array
			return count++;
		}

		void Remove(T element)
		{
			// Make sure the element actually exists
			T indexOfElementToDelete;
			if (!Find(element, indexOfElementToDelete))
			{
				return;
			}

			// Replace the deleted element with the last element in the dense array
			T lastElement = dense[count - 1];
			dense[indexOfElementToDelete] = lastElement;

			// Update the index of the last element to its new location
			sparse[lastElement] = indexOfElementToDelete;

			// Finally decreae the count
			count--;
		}

		constexpr T Capacity() const
		{
			return capacity;
		}

		constexpr T MaxValue() const
		{
			return maxValue;
		}

		T Count() const
		{
			return count;
		}

	private:
		// The tightly packed array containing the actual elements
		T* dense;

		// The sparse array containing the indexes of the elements in the dense array
		T* sparse;

		// The current number of elements in the dense array
		T count;
	};



	using EntityId = std::uint16_t;
	const EntityId MaxEntities = 10000; //std::numeric_limits<Entity>::max() - 1;
	const EntityId MaxEntityId = MaxEntities - 1; 
	using EntityVersion = std::uint16_t;

	using ComponentTypeId = std::uint8_t;
	const ComponentTypeId MaxComponentTypes = std::numeric_limits<ComponentTypeId>::max();
	using ComponentTypeHashId = size_t;
	using Signature = std::bitset<MaxComponentTypes>;

	struct Entity
	{
		EntityId id;
		EntityVersion version;
	};

	class EntityManager
	{
	public:
		void Init()
		{
			// Add all possible ids to the queue
			for (int i = 0; i < MaxEntities; i++)
			{
				availableEntityIds.push(i);
			}
		}

		Entity Create()
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
		}

		Signature GetEntitySignature(EntityId entityId)
		{
			return entitySignatures[entityId];
		}

		void SetEntitySignature(EntityId entityId, Signature newSignature)
		{
			entitySignatures[entityId] = newSignature;
		}

	private:
		// Currently available entity ids
		std::queue<EntityId> availableEntityIds;

		// Current versions for each entity id
		std::array<EntityVersion, MaxEntities> currentEntityVersions;

		// Current entity signatures
		std::array<Signature, MaxEntities> entitySignatures;
	};



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
				PG_ASSERT(false, "No component exists for entity id: {0}.", entityId);
			}

			// If it exists return the corresponding component
			return components[index];
		}

		void AddComponent(EntityId entityId, T component)
		{
			// Get the count before adding the new entity id
			EntityId count = entityIds.Count();

			// Add the new entity id to the list
			entityIds.Insert(entityId);

			// Now add the component to the components at the same index
			components[count] = component;
		}

		void RemoveComponent(EntityId entityId)
		{
			// Find the index of the entity
			EntityId indexOfRemovedElement;
			if (!entityIds.Find(entityId, indexOfRemovedElement))
			{
				PG_ASSERT(false, "No component exists for entity id: {0}.", entityId);
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
			ComponentTypeHashId hashId = HashId<T>();

			// Check the component doesn't already exist
			PG_ASSERT(componentTypeIds.find(hashId) == componentTypeIds.end(), "Tried to register a component that already exists: {0}.", STRINGIFY(T));
			
			// Insert the component hash id to the map
			componentTypeIds[hashId] = count;

			// Create the empty component array
			ComponentArray<T>* componentArray = new ComponentArray<T>();
			componentArrays[count] = Shared<IComponentArray>(static_cast<IComponentArray*>(componentArray));

			count++;
		}

		template <typename T>
		Shared<ComponentArray<T>> GetComponentArray()
		{
			// Get the hash id for this component
			ComponentTypeHashId hashId = HashId<T>();

			// Find the corresponding component id index
			auto& it = componentTypeIds.find(hashId);
			PG_ASSERT(it != componentTypeIds.end(), "Tried to access a component array that didn't exist: {0}.", STRINGIFY(T));

			// Return the component array at this index
			return std::static_pointer_cast<ComponentArray<T>>(componentArrays[(*it).second]);
		}

		template <typename T>
		T& GetComponent(EntityId entityId)
		{
			return GetComponentArray<T>()->GetComponent(entityId);
		}

		template <typename T>
		void AddComponent(EntityId entityId, T component)
		{
			GetComponentArray<T>()->AddComponent(entityId, component);
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
			return componentTypeIds[HashId<T>()];
		}

	private:
		// An array of component arrays
		std::array<Shared<IComponentArray>, MaxComponentTypes> componentArrays;

		// Sparse set containing the indexes of each component array for each type of component
		std::unordered_map<ComponentTypeHashId, ComponentTypeId> componentTypeIds;

		// Count of component arrays
		ComponentTypeId count = 0;

		// Returns a hash id for the given component type
		template <typename Type>
		static ComponentTypeHashId HashId() // TODO: Make constexpr with custom hash function
		{
			auto hash = std::hash<std::string>();
			return hash(std::string(__FUNCSIG__));
		}
	};



	class System
	{
	public:
		// The set of entity ids that this system relates to
		std::set<EntityId> entityIds;
	};

	class ECSManager;

	class SystemManager
	{
	public:
		template <typename T>
		Shared<T> RegisterSystem(ECSManager& ecsManager)
		{
			// Create a new instance of the system
			Shared<T> system = MakeShared<T>(ecsManager);

			// Add this new system to the vector of active systems
			systems.push_back(system);

			// Add the signature to the vector of signatures
			signatures.push_back(T::GetSignature(ecsManager));

			// Return the instance of the system back to the user
			return system;
		}

		void OnEntityDestroyed(EntityId entityId)
		{
			for (Shared<System> system : systems)
			{
				system->entityIds.erase(entityId);
			}
		}

		void OnEntitySignatureChanged(EntityId entityId, Signature entitySignature)
		{
			// For each system/signature
			for (int i = 0; i < systems.size(); i++)
			{
				Shared<System> system = systems[i];
				Signature& systemSignature = signatures[i];

				// If the signatures match, add the entityId
				if ((systemSignature & entitySignature) == systemSignature)
				{
					system->entityIds.insert(entityId);
				}
				// Otherwise, remove the entityId
				else
				{
					system->entityIds.erase(entityId);
				}
			}
		}

	private:
		// Vector containing all active systems
		std::vector<Shared<System>> systems;

		// Vector containing the corresponding system signatures
		std::vector<Signature> signatures;
	};



	class ECSManager
	{
	public:
		void Init()
		{
			entityManager.Init();
		}

		Entity CreateEntity()
		{
			return entityManager.Create();
		}

		void DestroyEntity(EntityId entityId)
		{
			entityManager.Destroy(entityId);

			componentManager.OnEntityDestroyed(entityId);
			systemManager.OnEntityDestroyed(entityId);
		}

		template <typename T>
		void RegisterComponent()
		{
			componentManager.RegisterComponent<T>();
		}

		template <typename T>
		Shared<ComponentArray<T>> GetComponentArray()
		{
			return componentManager.GetComponentArray<T>();
		}

		template <typename T>
		T& GetComponent(EntityId entityId)
		{
			PG_START_SCOPED_PROFILE("GET");
			return componentManager.GetComponent<T>(entityId);
			PG_END_SCOPED_PROFILE();
		}

		template <typename T>
		void AddComponent(EntityId entityId, T component)
		{
			componentManager.AddComponent(entityId, component);

			Signature entitySignature = entityManager.GetEntitySignature(entityId);
			entitySignature.set(componentManager.GetComponentTypeId<T>(), true);
			entityManager.SetEntitySignature(entityId, entitySignature);

			systemManager.OnEntitySignatureChanged(entityId, entitySignature);
		}

		template <typename T>
		void RemoveComponent(EntityId entityId)
		{
			componentManager.RemoveComponent<T>(entityId);

			Signature entitySignature = entityManager.GetEntitySignature(entityId);
			entitySignature.set(componentManager.GetComponentTypeId<T>(), false);
			entityManager.SetEntitySignature(entityId, entitySignature);

			systemManager.OnEntitySignatureChanged(entityId, entitySignature);
		}

		template <typename T>
		ComponentTypeId GetComponentTypeId()
		{
			return componentManager.GetComponentTypeId<T>();
		}

		template <typename T>
		Shared<T> RegisterSystem()
		{
			return systemManager.RegisterSystem<T>(*this);
		}

	private:
		EntityManager entityManager;
		ComponentManager componentManager;
		SystemManager systemManager;
	};
}