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

		template <typename T>
		friend class Safe;

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
		T* _GetComponentNoWarning()
		{
			try
			{
				return static_cast<T*>(components.at(T::ComponentName()));
			}
			catch (std::exception ex)
			{
				return nullptr;
			}
		}

		template<typename T>
		T* _GetComponent()
		{
			try
			{
				return static_cast<T*>(components.at(T::ComponentName()));
			}
			catch (std::exception ex)
			{
				PG_WARN("The component '{0}' does not exist for the game object '{1}'.", T::ComponentName(), this->name);

				return nullptr;
			}
		}

	public:
		template<typename T>
		T* GetComponentNoWarning()
		{
			return _GetComponentNoWarning<T>();
		}

		template<typename T>
		T* GetComponent()
		{
			return _GetComponent<T>();
		}

		template<>
		BoxCollider* GetComponentNoWarning<BoxCollider>()
		{
			return boxCollider;
		}

		template<>
		BoxCollider* GetComponent<BoxCollider>()
		{
			if (boxCollider == nullptr)
			{
				PG_WARN("The component '{0}' does not exist for the game object '{1}'.", BoxCollider::ComponentName(), this->name);
			}

			return boxCollider;
		}

		template<>
		MeshRenderer* GetComponentNoWarning<MeshRenderer>()
		{
			return meshRenderer;
		}
		
		template<>
		MeshRenderer* GetComponent<MeshRenderer>()
		{
			if (meshRenderer == nullptr)
			{
				PG_WARN("The component '{0}' does not exist for the game object '{1}'.", MeshRenderer::ComponentName(), this->name);
			}

			return meshRenderer;
		}

		template<>
		RigidBody* GetComponentNoWarning<RigidBody>()
		{
			return rigidBody;
		}

		template<>
		RigidBody* GetComponent<RigidBody>()
		{
			if (rigidBody == nullptr)
			{
				PG_WARN("The component '{0}' does not exist for the game object '{1}'.", RigidBody::ComponentName(), this->name);
			}

			return rigidBody;
		}

		template<>
		Transform* GetComponentNoWarning<Transform>()
		{
			return transform;
		}

		template<>
		Transform* GetComponent<Transform>()
		{
			if (transform == nullptr)
			{
				PG_WARN("The component '{0}' does not exist for the game object '{1}'.", Transform::ComponentName(), this->name);
			}

			return transform;
		}

		template<typename T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			T* component = new T(std::forward<Args>(args)...);
			
			AddComponentCommon(component);

			return component;
		}

		template<typename T, typename U>
		T* AddComponent(std::initializer_list<U> initList)
		{
			T* component = new T(initList);

			AddComponentCommon(component);

			return component;
		}

	private:
		template<typename T>
		void AddComponentCommon(T* component)
		{
			component->gameObject = this;

			Component* componentBase = static_cast<Component*>(component);
			components[T::ComponentName()] = componentBase;

			if (T::ComponentName() == BoxCollider::ComponentName())  boxCollider = static_cast<BoxCollider*>(componentBase);
			else if (T::ComponentName() == MeshRenderer::ComponentName()) meshRenderer = static_cast<MeshRenderer*>(componentBase);
			else if (T::ComponentName() == RigidBody::ComponentName())    rigidBody = static_cast<RigidBody*>(componentBase);
			else if (T::ComponentName() == Transform::ComponentName())    transform = static_cast<Transform*>(componentBase);

			if (*exists)
			{
				Scene::AddComponent(component);
			}
		}

	public:
		template<typename T>
		bool RemoveComponent()
		{
			auto it = components.find(T::ComponentName());

			if (it != components.end())
			{
				if (*exists)
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

	protected:
		virtual void Init();

		virtual void Update(float dt);
		virtual void FrameUpdate(float alpha);

	private:
		std::string name;

		std::unordered_map<std::string, Component*> components;

		bool* exists;
		int* refCount;

		// Commonly accessed components that we can cache
		BoxCollider* boxCollider;
		MeshRenderer* meshRenderer;
		RigidBody* rigidBody;
		Transform* transform;
	};

	template <typename T>
	class Safe
	{
		typedef typename std::enable_if<std::is_base_of<GameObject, T>::value>::type check;

	public:
		friend class Safe<GameObject>;

		Safe(T* gameObject = nullptr)
			: gameObject(gameObject)
			, exists(nullptr)
			, refCount(nullptr)
		{
			if (gameObject != nullptr)
			{
				exists = gameObject->exists;
				refCount = gameObject->refCount;
				(*refCount)++;
			}
			else
			{
				exists = nullptr;
				refCount = nullptr;
			}
		}

		Safe(GameObject* gameObject)
			: gameObject(static_cast<T*>(gameObject))
			, exists(nullptr)
			, refCount(nullptr)
		{
			if (gameObject != nullptr)
			{
				exists = gameObject->exists;
				refCount = gameObject->refCount;
				(*refCount)++;
			}
			else
			{
				exists = nullptr;
				refCount = nullptr;
			}
		}

		Safe(Safe<T>& safeGameObject)
			: gameObject(safeGameObject.gameObject)
			, exists(safeGameObject.exists)
			, refCount(safeGameObject.refCount)
		{
			if (refCount != nullptr)
			{
				(*refCount)++;
			}
		}

		Safe(Safe<GameObject>& safeGameObject)
			: gameObject(static_cast<T*>(safeGameObject.gameObject))
			, exists(safeGameObject.exists)
			, refCount(safeGameObject.refCount)
		{
			if (refCount != nullptr)
			{
				(*refCount)++;
			}
		}

		~Safe()
		{
			TryShrink();
		}

		Safe<T>& operator=(Safe<T>& safeGameObject)
		{
			TryShrink();

			gameObject = safeGameObject.gameObject;
			exists = safeGameObject.exists;
			refCount = safeGameObject.refCount;
			
			if (refCount != nullptr)
			{
				(*refCount)++;
			}

			return *this;
		}

		Safe<T>& operator=(Safe<GameObject>& safeGameObject)
		{
			TryShrink();

			gameObject = static_cast<T*>(safeGameObject.gameObject);
			exists = safeGameObject.exists;
			refCount = safeGameObject.refCount;

			if (refCount != nullptr)
			{
				(*refCount)++;
			}

			return *this;
		}

		T& operator*()
		{
			return *gameObject;
		}

		T* operator->()
		{
			return gameObject;
		}

		bool Exists()
		{
			return exists != nullptr && *exists;
		}

	private:
		void TryShrink()
		{
			if (refCount != nullptr)
			{
				(*refCount)--;
				if ((*refCount) == 0)
				{
					delete exists;
					delete refCount;
				}
			}
		}

		T* gameObject;
		bool* exists;
		int* refCount;
	};

	template <>
	class Safe<GameObject> // TODO: Reduce copypasta?
	{
	public:
		template <typename T>
		friend class Safe;

		Safe(GameObject* gameObject = nullptr)
			: gameObject(gameObject)
			, exists(nullptr)
			, refCount(nullptr)
		{
			if (gameObject != nullptr)
			{
				exists = gameObject->exists;
				refCount = gameObject->refCount;
				(*refCount)++;
			}
			else
			{
				exists = nullptr;
				refCount = nullptr;
			}
		}

		template <typename T>
		Safe(Safe<T>& safeGameObject)
			: gameObject(safeGameObject.gameObject)
			, exists(safeGameObject.exists)
			, refCount(safeGameObject.refCount)
		{
			if (refCount != nullptr)
			{
				(*refCount)++;
			}
		}

		~Safe()
		{
			TryShrink();
		}

		template <typename T>
		Safe<GameObject>& operator=(Safe<T>& safeGameObject)
		{
			TryShrink();

			gameObject = safeGameObject.gameObject;
			exists = safeGameObject.exists;
			refCount = safeGameObject.refCount;

			if (refCount != nullptr)
			{
				(*refCount)++;
			}

			return *this;
		}

		GameObject* operator->()
		{
			return gameObject;
		}

		GameObject& operator*()
		{
			return *gameObject;
		}

		bool Exists()
		{
			return exists != nullptr && *exists;
		}

		template <typename T>
		T& To()
		{
			return static_cast<T&>(*gameObject);
		}

	private:
		void TryShrink()
		{
			if (refCount != nullptr)
			{
				(*refCount)--;
				if ((*refCount) == 0)
				{
					delete exists;
					delete refCount;
				}
			}
		}

		GameObject* gameObject;
		bool* exists;
		int* refCount;
	};
}