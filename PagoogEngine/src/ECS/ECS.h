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
#include "Maths/Maths.h"
#include "Maths/Collisions.h"
#include "Render/Mesh/Mesh.h"
#include "Render/Material/Material.h"
#include "Util/Hash.h"

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
			return index < count&& dense[index] == element;
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

	struct EntityInfo
	{
		EntityId id;
		EntityVersion version;
	};

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
		void OnSystemRegistered(Shared<T> system)
		{
			// Check if any entities' signature match
			for (int i = 0; i < MaxEntities; i++)
			{
				Signature entitySignature = entitySignatures[i];
				Signature systemSignature = T::GetSignature();

				// If the signatures match, add the entity id
				if ((systemSignature & entitySignature) == systemSignature)
				{
					system->entityIds.insert(entityId);
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



	struct ECSTransform
	{
		Vec3 position = Vec3(0.0f, 0.0f, 0.0f);
		Quat orientation = Quat(Vec3(0.0f, 0.0f, 0.0f));
		Vec3 scale = Vec3(1.0f, 1.0f, 1.0f);

		Vec3 prevPosition = Vec3(0.0f, 0.0f, 0.0f);
		Quat prevOrientation = Quat(Vec3(0.0f, 0.0f, 0.0f));
		Vec3 prevScale = Vec3(1.0f, 1.0f, 1.0f);
	};

	struct ECSRigidBody
	{
		Vec3 force = Vec3(0.0f, 0.0f, 0.0f);
		Vec3 velocity = Vec3(0.0f, 0.0f, 0.0f);
		float mass = 1.0f;
		float dragCoef = 1.0f;
	};

	struct ECSBoxCollider
	{
		AABB<3> aabb = AABB<3>({ 1.0f, 1.0f, 1.0f });
		float stickiness = 0.5f;
	};

	struct ECSMeshRenderer
	{
		Shared<Mesh> mesh = nullptr;
		Shared<Material> material = nullptr;
	};

	class Camera;
	struct ECSCamera
	{
		Shared<Camera> camera;
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
			static const ComponentTypeHashId hashId = HashId<T, ComponentTypeHashId>();

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
			static const ComponentTypeHashId hashId = HashId<T, ComponentTypeHashId>();

			// Find the corresponding component id index
			PG_ASSERT(componentTypeIds.find(hashId) != componentTypeIds.end(), "Tried to access a component array that didn't exist: {0}.", STRINGIFY(T));

			// Return the component array at this index
			return std::static_pointer_cast<ComponentArray<T>>(componentArrays[componentTypeIds[hashId]]);
		}

		template <typename T>
		T& GetComponent(EntityId entityId)
		{
			return GetComponentArray<T>()->GetComponent(entityId);
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
			static const ComponentTypeHashId hashId = HashId<T, ComponentTypeHashId>();

			return componentTypeIds[hashId];
		}

	private:
		// An array of component arrays
		std::array<Shared<IComponentArray>, MaxComponentTypes> componentArrays;

		// Sparse set containing the indexes of each component array for each type of component
		std::unordered_map<ComponentTypeHashId, ComponentTypeId> componentTypeIds;

		// Count of component arrays
		ComponentTypeId count = 0;
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
			systemSignatures.push_back(T::GetSignature(ecsManager));

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
				Signature& systemSignature = systemSignatures[i];

				// If the signatures match, add the entity id
				if ((systemSignature & entitySignature) == systemSignature)
				{
					system->entityIds.insert(entityId);
				}
				// Otherwise, remove the entity id
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
		std::vector<Signature> systemSignatures;
	};

	class TransformSystem : public System
	{
	public:
		TransformSystem(ECSManager& ecsManager)
			: ecsManager(ecsManager)
		{
		}

		static Signature GetSignature(ECSManager& ecsManager);

		void Update(float dt);

	private:
		ECSManager& ecsManager;
	};

	class PhysicsSystem : public System
	{
	public:
		PhysicsSystem(ECSManager& ecsManager)
			: ecsManager(ecsManager)
		{
		}

		static Signature GetSignature(ECSManager& ecsManager);

		void Update(float dt);

	private:
		ECSManager& ecsManager;
	};

	class CollisionsSystem : public System
	{
	public:
		CollisionsSystem(ECSManager& ecsManager)
			: ecsManager(ecsManager)
		{
		}

		static Signature GetSignature(ECSManager& ecsManager);

		void Update(float dt);

	private:
		ECSManager& ecsManager;
	};

	class CameraUpdateViewSystem : public System
	{
	public:
		CameraUpdateViewSystem(ECSManager& ecsManager)
			: ecsManager(ecsManager)
		{
		}

		static Signature GetSignature(ECSManager& ecsManager);

		void UpdateView();

	private:
		ECSManager& ecsManager;
	};

	class MeshRendererSystem : public System
	{
	public:
		MeshRendererSystem(ECSManager& ecsManager)
			: ecsManager(ecsManager)
		{
		}

		static Signature GetSignature(ECSManager& ecsManager);

		void FrameUpdate(float alpha);

	private:
		ECSManager& ecsManager;
	};

	struct RayCastResult
	{
		bool hit = false;
		EntityId entityId = 0;
	};

	class RayCastSystem : public System
	{
	public:
		RayCastSystem(ECSManager& ecsManager)
			: ecsManager(ecsManager)
		{
		}

		static Signature GetSignature(ECSManager& ecsManager);

		RayCastResult RayCast(Vec3 position, Vec3 direction, EntityId entityIdToIgnore);

	private:
		ECSManager& ecsManager;
	};



	class Entity;
	class Scene;

	class ECSManager
	{
	public:
		Shared<TransformSystem>	transformSystem;
		Shared<PhysicsSystem> physicsSystem;
		Shared<CollisionsSystem> collisionsSystem;
		Shared<CameraUpdateViewSystem> cameraUpdateViewSystem;
		Shared<RayCastSystem> rayCastSystem;

		ECSManager(Scene* scene)
			: scene(scene)
		{
		}

		Entity CreateEntity();

		template <typename T, typename... Args>
		T CreateEntity(Args&&... args);

		void DestroyEntity(EntityId entityId)
		{
			entityManager.Destroy(entityId);

			componentManager.OnEntityDestroyed(entityId);
			systemManager.OnEntityDestroyed(entityId);
		}

		EntityVersion GetVersion(EntityId entityId) const
		{
			return entityManager.GetVersion(entityId);
		}

		bool IsEntityValid(EntityInfo entityInfo) const
		{
			return entityManager.IsEntityValid(entityInfo);
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
			return componentManager.GetComponent<T>(entityId);
		}

		template <typename T>
		T& AddComponent(EntityId entityId, const T& component)
		{
			T& copiedComponent = componentManager.AddComponent(entityId, component);

			Signature entitySignature = entityManager.GetEntitySignature(entityId);
			entitySignature.set(componentManager.GetComponentTypeId<T>(), true);
			entityManager.SetEntitySignature(entityId, entitySignature);
			systemManager.OnEntitySignatureChanged(entityId, entitySignature);

			return copiedComponent;
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

		void Init()
		{
			entityManager.Init();

			RegisterComponent<ECSTransform>();
			RegisterComponent<ECSRigidBody>();
			RegisterComponent<ECSBoxCollider>();
			RegisterComponent<ECSMeshRenderer>();
			RegisterComponent<ECSCamera>();

			transformSystem = RegisterSystem<TransformSystem>();
			physicsSystem = RegisterSystem<PhysicsSystem>();
			collisionsSystem = RegisterSystem<CollisionsSystem>();
			cameraUpdateViewSystem = RegisterSystem<CameraUpdateViewSystem>();
			rayCastSystem = RegisterSystem<RayCastSystem>();
		}

		Scene& GetScene() const { return *scene; }

	private:
		EntityManager entityManager;
		ComponentManager componentManager;
		SystemManager systemManager;

		// The scene the ecs manager is associated with
		Scene* scene;
	};



	class Entity
	{
	public:
		Entity(EntityInfo entityInfo = { 0, 0 }, ECSManager* ecsManager = { nullptr })
			: entityInfo(entityInfo)
			, ecsManager(ecsManager)
		{
		}

		Entity(EntityInfo entityInfo, ECSManager& ecsManager)
			: entityInfo(entityInfo)
			, ecsManager(&ecsManager)
		{
		}

		virtual void OnCreate() { }

		template <typename T>
		T& GetComponent()
		{
			return ecsManager->GetComponent<T>(GetId());
		}

		template <typename T>
		T& AddComponent(const T& component)
		{
			return ecsManager->AddComponent(GetId(), component);
		}

		template <typename T>
		void RemoveComponent()
		{
			ecsManager->RemoveComponent<T>(GetId());
		}

		bool IsValid() const
		{
			return ecsManager->IsEntityValid(entityInfo);
		}

		EntityId GetId() const { return entityInfo.id; }
		EntityVersion GetVersion() const { return entityInfo.version; }

		ECSManager& GetECSManager() const { return *ecsManager; }
		Scene& GetScene() const { return ecsManager->GetScene(); }

	private:
		EntityInfo entityInfo;
		ECSManager* ecsManager;
	};



	inline Entity ECSManager::CreateEntity()
	{
		return { entityManager.Create(), this };
	}

	template <typename T, typename... Args>
	inline T ECSManager::CreateEntity(Args&&... args)
	{
		// Create and construct the new entity from the give class
		T entity(entityManager.Create(), *this, std::forward<Args>(args)...);

		// Call the on create function
		entity.OnCreate();

		// Return the entity
		return entity;
	}
}