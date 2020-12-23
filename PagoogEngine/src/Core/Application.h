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
	
		virtual void ActionCallback(InputPackage& inputPackage, float dt);

		void AddLayer(Layer* layer);

	protected:
		InputManager inputManager;

		Window* window;

	private:
		std::vector<Layer*> layers;
	};

	Application* CreateApplication();
}

