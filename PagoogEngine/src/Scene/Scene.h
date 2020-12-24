#pragma once

#include "Layer/Layer.h"
#include "Event/Event.h"

namespace PEngine
{
	class Scene
	{
	public:
		template <typename T>
		static T* CreateGameObject(const T& gameObject)
		{
			T* newGameObject = new T(gameObject);

			AddGameObject(newGameObject);

			return newGameObject;
		}

		static void AddGameObject(GameObject* gameObject);

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

