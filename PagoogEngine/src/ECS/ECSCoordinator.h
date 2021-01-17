#pragma once

#include "Entity/EntityManager.h"
#include "Component/ComponentManager.h"
#include "System/SystemManager.h"

namespace PEngine
{
	class ECSCoordinator
	{
	public:
		void Init()
		{
			// Create pointers to each manager
			componentManager = MakeUnique<ComponentManager>();
			entityManager = MakeUnique<EntityManager>();
			systemManager = MakeUnique<SystemManager>();
		}


		// Entity methods
		Entity CreateEntity()
		{
			return entityManager->CreateEntity();
		}

		void DestroyEntity(Entity entity)
		{
			entityManager->DestroyEntity(entity);

			componentManager->EntityDestroyed(entity);
			systemManager->EntityDestroyed(entity);
		}


		// Component methods
		template<typename T>
		void RegisterComponent()
		{
			componentManager->RegisterComponent<T>();
		}

		template<typename T>
		void AddComponent(Entity entity, T component)
		{
			componentManager->AddComponent<T>(entity, component);

			auto signature = entityManager->GetSignature(entity);
			signature.set(componentManager->GetComponentType<T>(), true);
			entityManager->SetSignature(entity, signature);

			systemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		void RemoveComponent(Entity entity)
		{
			componentManager->RemoveComponent<T>(entity);

			auto signature = entityManager->GetSignature(entity);
			signature.set(componentManager->GetComponentType<T>(), false);
			entityManager->SetSignature(entity, signature);

			systemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		T& GetComponent(Entity entity)
		{
			return componentManager->GetComponent<T>(entity);
		}

		template<typename T>
		ComponentType GetComponentType()
		{
			return componentManager->GetComponentType<T>();
		}


		// System methods
		template<typename T>
		Shared<T> RegisterSystem()
		{
			return systemManager->RegisterSystem<T>();
		}

		template<typename T>
		void SetSystemSignature(Signature signature)
		{
			systemManager->SetSignature<T>(signature);
		}

	private:
		Unique<ComponentManager> componentManager;
		Unique<EntityManager> entityManager;
		Unique<SystemManager> systemManager;
	};
}