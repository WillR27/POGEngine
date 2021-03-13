#pragma once

#include "Window/Window.h"

namespace Pagoog::Core
{
	class Application
	{
	public:
		Application(std::string name = "Pagoog");

		virtual ~Application();

		void PreInit();
		virtual void Init() = 0;
		void PostInit();

		void Run();

		const Window& GetWindow() { return *window; }

	private:
		std::unique_ptr<Window> window;

		std::string name;
	};

	std::unique_ptr<Application> CreateApplication();
}

