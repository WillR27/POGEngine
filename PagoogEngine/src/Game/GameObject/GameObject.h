#pragma once

#include "Game/GameObject/Components/Components.h"
#include "Scene/Scene.h"

namespace PEngine
{
	class GameObject
	{
	public:
		friend class Scene;

		GameObject(std::string name = "Game Object");
		virtual ~GameObject();

		template<typename T>
		bool HasComponent()
		{
			try
			{
				components.at(T::ComponentName());
			}
			catch (std::exception ex)
			{
				return false;
			}

			return true;
		}

		template<typename T>
		T* GetComponent()
		{
			try
			{
				return static_cast<T*>(components.at(T::ComponentName()));
			}
			catch (std::exception ex)
			{
				//PG_WARN("Component does not exist! The component \"{0}\" does not exist for the game object \"{1}\".", T::ComponentName(), this->name);
				return nullptr;
			}
		}

		template<typename T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			T* component = new T(std::forward<Args>(args)...);
			component->gameObject = this;

			components[T::ComponentName()] = static_cast<Component*>(component);

			if (inScene)
			{
				Scene::AddComponent(component);
			}

			return component;
		}

		BoxCollider& GetBoxCollider();
		MeshRenderer& GetMeshRenderer();
		RigidBody& GetRigidBody();
		Transform& GetTransform();

		void SetName(std::string name);
		std::string GetName() const;

		bool InScene() const;

	protected:
		virtual void Init() = 0;

	private:
		std::string name;

		std::unordered_map<std::string, Component*> components;

		bool inScene;

		// Commonly accessed components that we can cache
		BoxCollider* boxCollider;
		MeshRenderer* meshRenderer;
		RigidBody* rigidBody;
		Transform* transform;
	};
}