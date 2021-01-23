#pragma once

#include "Event/Event.h"
#include "Layer/Layer.h"

namespace PEngine
{
	class Scene
	{
	public:
		friend class Application;

		Scene(std::string name = "Scene");
		virtual ~Scene();

		virtual void Init();

		virtual void Update(float dt);
		virtual void FrameUpdate(float alpha);

		virtual void HandleEvent(Event& e);

		void AddLayer(Layer* layer);
		
	protected:
		std::vector<Layer*> layers;

	private:
		static Scene* ActiveScene;

		std::string name;
	};
}

