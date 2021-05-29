#pragma once

#include "Component.h"
#include "Entity.h"
#include "System.h"

namespace POG::Core
{
	class Entity;
	class ECSManager final
	{
	public:
		/*std::shared_ptr<TransformSystem>	transformSystem;
		std::shared_ptr<PhysicsSystem> physicsSystem;
		std::shared_ptr<CollisionsSystem> collisionsSystem;
		std::shared_ptr<CameraUpdateViewSystem> cameraUpdateViewSystem;
		std::shared_ptr<RayCastSystem> rayCastSystem;*/

		ECSManager()
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

		bool IsValid(EntityInfo entityInfo) const
		{
			return entityManager.IsValid(entityInfo);
		}

		std::string GetName(EntityId entityId) const
		{
			return entityManager.GetName(entityId);
		}

		void SetName(EntityId entityId, std::string name)
		{
			entityManager.SetName(entityId, name);
		}

		std::vector<EntityId> GetChildren(EntityId entityId) const
		{
			return entityManager.GetChildren(entityId);
		}

		bool HasChildren(EntityId entityId) const
		{
			return entityManager.HasChildren(entityId);
		}

		EntityId GetParent(EntityId entityId) const
		{
			return entityManager.GetParent(entityId);
		}

		bool HasParent(EntityId entityId) const
		{
			return entityManager.HasParent(entityId);
		}

		void SetParent(EntityId entityId, EntityId parentId)
		{
			entityManager.SetParent(entityId, parentId);
		}

		std::vector<EntityId> GetUsedEntityIds() const
		{
			return entityManager.GetUsedEntityIds();
		}

		bool IsUsed(EntityId entityId) const
		{
			return entityManager.IsUsed(entityId);
		}

		template <typename T>
		void RegisterComponent()
		{
			componentManager.RegisterComponent<T>();
		}

		template <typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray()
		{
			return componentManager.GetComponentArray<T>();
		}

		template <typename T>
		bool HasComponent(EntityId entityId)
		{
			Signature entitySignature = entityManager.GetEntitySignature(entityId);

			return entitySignature[componentManager.GetComponentTypeId<T>()];
		}

		template <typename T>
		T& GetComponent(EntityId entityId)
		{
			return componentManager.GetComponent<T>(entityId);
		}

		template <typename T>
		void SetComponent(EntityId entityId, T component)
		{
			componentManager.SetComponent(entityId, component);
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

		template <typename T, typename... Args>
		std::shared_ptr<T> RegisterSystem(Args&&... args)
		{
			return systemManager.RegisterSystem<T>(*this, std::forward<Args>(args)...);
		}

		void Init()
		{
			entityManager.Init();
		}

	private:
		EntityManager entityManager;
		ComponentManager componentManager;
		SystemManager systemManager;
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

		operator EntityId () { return GetId(); }

		template <typename T>
		T& GetComponent()
		{
			return ecsManager->GetComponent<T>(GetId());
		}

		template <typename T>
		void SetComponent(EntityId entityId, T component)
		{
			ecsManager->SetComponent(entityId, component);
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
			return ecsManager->IsValid(entityInfo);
		}

		std::vector<EntityId> GetChildren() const
		{
			return ecsManager->GetChildren(GetId());
		}

		std::string GetName() const
		{
			return ecsManager->GetName(GetId());
		}

		void SetName(std::string name)
		{
			ecsManager->SetName(GetId(), name);
		}

		bool HasChildren() const
		{
			return ecsManager->HasChildren(GetId());
		}

		EntityId GetParent() const
		{
			return ecsManager->GetParent(GetId());
		}

		bool HasParent() const
		{
			return ecsManager->HasParent(GetId());
		}

		void SetParent(EntityId parentId)
		{
			ecsManager->SetParent(GetId(), parentId);
		}

		EntityId GetId() const { return entityInfo.id; }
		EntityVersion GetVersion() const { return entityInfo.version; }

		ECSManager& GetECSManager() const { return *ecsManager; }

		//MeshManager& GetMeshManager();
		//MaterialManager& GetMaterialManager();
		//ShaderManager& GetShaderManager();

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

		// Return the entity
		return entity;
	}
}