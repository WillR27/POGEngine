#pragma once

#include "Event/Event.h"
#include "Layer/Layer.h"
#include "Game/GameObject/Components/Components.h"

namespace PEngine
{
	class GameObject;

	class Scene
	{
	public:
		friend class Application;
		friend class GameObject;

		template <typename T>
		static T* AddGameObject(const T& gameObject) // TODO: Rename to add
		{
			T* newGameObject = new T(gameObject);

			_AddGameObject(newGameObject);

			return newGameObject;
		}

		template <typename T, typename... Args>
		static T* CreateGameObject(Args... args)
		{
			T* newGameObject = new T(std::forward(args)...);

			_AddGameObject(newGameObject);

			return newGameObject;
		}

	private:
		template <typename T>
		static void AddComponent(T* component)
		{
			int index = IndexOf(Layer::ActiveLayer->gameObjects, component->gameObject);

			if (index != -1)
			{
				if (T::ComponentName() == BoxCollider::ComponentName())
				{
					Layer::ActiveLayer->boxColliders[index] = reinterpret_cast<BoxCollider*>(component);
				}
				else if (T::ComponentName() == Camera::ComponentName())
				{
					Layer::ActiveLayer->cameras[index] = reinterpret_cast<Camera*>(component);
				}
				else if (T::ComponentName() == MeshRenderer::ComponentName())
				{
					Layer::ActiveLayer->meshRenderers[index] = reinterpret_cast<MeshRenderer*>(component);
				}
				else if (T::ComponentName() == RigidBody::ComponentName())
				{
					Layer::ActiveLayer->rigidBodies[index] = reinterpret_cast<RigidBody*>(component);
				}
				else if (T::ComponentName() == Transform::ComponentName())
				{
					Layer::ActiveLayer->transforms[index] = reinterpret_cast<Transform*>(component);
				}
			}
		}

		template <typename T>
		static void RemoveComponent(T* component)
		{
			int index = IndexOf(Layer::ActiveLayer->gameObjects, component->gameObject);

			if (index != -1)
			{
				if (T::ComponentName() == BoxCollider::ComponentName())
				{
					Layer::ActiveLayer->boxColliders[index] = nullptr;
				}
				else if (T::ComponentName() == Camera::ComponentName())
				{
					Layer::ActiveLayer->cameras[index] = nullptr;
				}
				else if (T::ComponentName() == MeshRenderer::ComponentName())
				{
					Layer::ActiveLayer->meshRenderers[index] = nullptr;
				}
				else if (T::ComponentName() == RigidBody::ComponentName())
				{
					Layer::ActiveLayer->rigidBodies[index] = nullptr;
				}
				else if (T::ComponentName() == Transform::ComponentName())
				{
					Layer::ActiveLayer->transforms[index] = nullptr;
				}
			}
		}

		static void _AddGameObject(GameObject* gameObject);
		
	public:
		static void RemoveGameObject(GameObject* gameObject);
		static void DeleteGameObject(GameObject* gameObject);

		static GameObject* RayCast(Vec3 position, Vec3 direction, const GameObject& objectToIgnore);

		Scene(std::string name);
		~Scene();

		void Init();

		void Update(float dt);
		void FrameUpdate(float dt);

		void HandleEvent(Event& e);

		void AddLayer(Layer* layer);

	private:
		static Scene* ActiveScene;

		std::string name;

		std::vector<Layer*> layers;

		GameObject* _RayCast(Vec3 position, Vec3 direction, const GameObject& objectToIgnore) const;
	};
}

