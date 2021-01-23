#pragma once

#include "Event/Event.h"
#include "Layer/Layer.h"
#include "Scene/Scene.h"
#include "Window/Window.h"

namespace PEngine
{
	class Application
	{
	public:
		Application();
		~Application();

		void PreInit();
		virtual void Init() = 0;
		void PostInit();
		void Run();

		void HandleEvent(Event& e);
	
		virtual void ActionCallback(InputPackage& inputPackage, float dt);

		void AddScene(Scene* scene);

	protected:
		InputManager inputManager;

		Window* window;

	private:
		std::vector<Scene*> scenes;
	};

	Application* CreateApplication();
}

