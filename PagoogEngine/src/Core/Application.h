#pragma once

#include "Window/Window.h"
#include "Event/Event.h"
#include "Layer/Layer.h"

namespace PEngine
{
	class Application
	{
	public:
		Application();
		~Application();

		virtual void Init();
		void Run();

		void HandleEvent(Event& e);

		void AddLayer(Layer* layer);
	
	private:
		Window* window;

		std::vector<Layer*> layers;
	};

	Application* CreateApplication();
}

