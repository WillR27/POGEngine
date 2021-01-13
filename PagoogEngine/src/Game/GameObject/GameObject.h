#pragma once

#include "Game/GameObject/Components/Components.h"
#include "Scene/Scene.h"

namespace PEngine
{
	class GameObject
	{
	public:
		friend class Layer;
		friend class Scene;

		GameObject(std::string name = "Game Object");
		virtual ~GameObject();

		GameObject(const GameObject& gameObject);

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

	private:
		template<typename T>
		T* _GetComponent(bool warn = true)
		{
			try
			{
				return static_cast<T*>(components.at(T::ComponentName()));
			}
			catch (std::exception ex)
			{
				if (warn)
				{
					PG_WARN("The component '{0}' does not exist for the game object '{1}'.", T::ComponentName(), this->name);
				}

				return nullptr;
			}
		}

	public:
		template<typename T>
		T* GetComponent(bool warn = true)
		{
			return _GetComponent<T>(warn);
		}

		template<>
		BoxCollider* GetComponent<BoxCollider>(bool warn)
		{
			return boxCollider != nullptr ? boxCollider : boxCollider = _GetComponent<BoxCollider>(warn);
		}

		template<>
		MeshRenderer* GetComponent<MeshRenderer>(bool warn)
		{
			return meshRenderer != nullptr ? meshRenderer : meshRenderer = _GetComponent<MeshRenderer>(warn);
		}

		template<>
		RigidBody* GetComponent<RigidBody>(bool warn)
		{
			return rigidBody != nullptr ? rigidBody : rigidBody = _GetComponent<RigidBody>(warn);
		}

		template<>
		Transform* GetComponent<Transform>(bool warn)
		{
			return transform != nullptr ? transform : transform = _GetComponent<Transform>(warn);
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

		template<typename T, typename U>
		T* AddComponent(std::initializer_list<U> initList)
		{
			T* component = new T(initList);
			component->gameObject = this;

			components[T::ComponentName()] = static_cast<Component*>(component);

			if (inScene)
			{
				Scene::AddComponent(component);
			}

			return component;
		}

		template<typename T>
		bool RemoveComponent()
		{
			auto it = components.find(T::ComponentName());

			if (it != components.end())
			{
				if (inScene)
				{
					Scene::RemoveComponent(static_cast<T*>((*it).second));
				}

				delete static_cast<T*>((*it).second);

				components.erase(it);

				return true;
			}

			return false;
		}

		void SetName(std::string name);
		std::string GetName() const;

		bool InScene() const;

	protected:
		virtual void Init();

		virtual void Update(float dt);
		virtual void FrameUpdate(float alpha);

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