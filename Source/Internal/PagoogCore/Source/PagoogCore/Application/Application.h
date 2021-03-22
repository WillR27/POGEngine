#pragma once

#include "PagoogCoreAPI.h"

#include "PagoogCore/Window/Window.h"

namespace Pagoog::Core
{
	class Application
	{
	public:
		PG_CORE_API Application(std::string name = "Pagoog");

		PG_CORE_API virtual ~Application();

		PG_CORE_API void PreInit();
		PG_CORE_API virtual void Init() = 0;
		PG_CORE_API void PostInit();

		PG_CORE_API void Run();

		const Window& GetWindow() { return *window; }

	private:
		std::unique_ptr<Window> window;

		std::string name;
	};

	std::unique_ptr<Application> CreateApplication();
}

