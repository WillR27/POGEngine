#pragma once

#include "Event/Event.h"
#include "Layer/Layer.h"

namespace PEngine
{
	class Scene
	{
	public:
		friend class Application;

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
	};
}

