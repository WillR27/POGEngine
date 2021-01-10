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
		friend class GameObject;

		template <typename T>
		static T& CreateGameObject(const T& gameObject) // TODO: Rename to add
		{
			T* newGameObject = new T(gameObject);

			AddGameObject(newGameObject);

			return *newGameObject;
		}

		template <typename T, typename... Args>
		static T& AddGameObject(Args... args)
		{
			T* newGameObject = new T(std::forward(args)...);

			AddGameObject(newGameObject);

			return *newGameObject;
		}

	private:
		template <typename T>
		static void AddComponent(T* component)
		{
			int index = IndexOf(ActiveLayer->gameObjects, component->gameObject);

			if (index != -1)
			{
				if (T::ComponentName() == BoxCollider::ComponentName())
				{
					ActiveLayer->boxColliders[index] = reinterpret_cast<BoxCollider*>(component);
				}
				else if (T::ComponentName() == MeshRenderer::ComponentName())
				{
					ActiveLayer->meshRenderers[index] = reinterpret_cast<MeshRenderer*>(component);
				}
				else if (T::ComponentName() == RigidBody::ComponentName())
				{
					ActiveLayer->rigidBodies[index] = reinterpret_cast<RigidBody*>(component);
				}
				else if (T::ComponentName() == Transform::ComponentName())
				{
					ActiveLayer->transforms[index] = reinterpret_cast<Transform*>(component);
				}
			}
		}

		static void AddGameObject(GameObject* gameObject);

	public:
		Scene(std::string name);
		~Scene();

		void Init();

		void Update(float dt);
		void FrameUpdate(float dt);

		void HandleEvent(Event& e);

		void AddLayer(Layer* layer);

	private:
		static Layer* ActiveLayer;

		std::string name;

		std::vector<Layer*> layers;
	};
}

