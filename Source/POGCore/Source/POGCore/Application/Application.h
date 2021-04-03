#pragma once

#include "POGCoreAPI.h"

#include "POGCore/Window/Window.h"

namespace POG::Core
{
	class Application
	{
	public:
		POG_CORE_API Application(std::string name = "POG");

		POG_CORE_API virtual ~Application();

		POG_CORE_API void PreInit();
		POG_CORE_API virtual void Init() = 0;
		POG_CORE_API void PostInit();

		POG_CORE_API void Run();

		const Window& GetWindow() { return *window; }

	private:
		std::unique_ptr<Window> window;

		std::string name;
	};

	std::unique_ptr<Application> CreateApplication();
}

