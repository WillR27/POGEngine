#pragma once

#include "Event/Event.h"

namespace PEngine
{
	class GameObject;
	class Component;
	class Layer;

	class Scene
	{
	public:
		friend class GameObject;

		template <typename T>
		static T* CreateGameObject(const T& gameObject)
		{
			T* newGameObject = new T(gameObject);

			AddGameObject(newGameObject);

			return newGameObject;
		}

		template <typename T, typename... Args>
		static T& AddGameObject(Args... args)
		{
			T* newGameObject = new T(std::forward(args)...);

			AddGameObject(newGameObject);

			return *newGameObject;
		}

	private:
		static void AddGameObject(GameObject* gameObject);
		static void AddComponent(Component* component);

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

