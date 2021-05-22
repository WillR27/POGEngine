#pragma once

#include "Component.h"
#include "Entity.h"
#include "System.h"

namespace POG::Core
{
	class Entity;
	class ECSManager
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
		std::shared_ptr<ComponentArray<T>> GetComponentArray()
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

		template <typename T, typename... Args>
		std::shared_ptr<T> RegisterSystem(Args&&... args)
		{
			return systemManager.RegisterSystem<T>(*this, std::forward<Args>(args)...);
		}

		void Init()
		{
			entityManager.Init();

			//RegisterComponent<Transform>();
			//RegisterComponent<RigidBody>();
			//RegisterComponent<BoxCollider>();
			//RegisterComponent<MeshRenderer>();
			//RegisterComponent<AttachedCamera>();

			//transformSystem = RegisterSystem<TransformSystem>();
			//physicsSystem = RegisterSystem<PhysicsSystem>();
			//collisionsSystem = RegisterSystem<CollisionsSystem>();
			//cameraUpdateViewSystem = RegisterSystem<CameraUpdateViewSystem>();
			//rayCastSystem = RegisterSystem<RayCastSystem>();
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