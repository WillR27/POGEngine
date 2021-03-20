#include "PagoogCorePCH.h"
#include "Application.h"

#include "PagoogLog.h"

namespace Pagoog::Core
{
	Application::Application(std::string name)
		: window(nullptr)
		, name(name)
	{
		PG_INFO("Creating application \"{0}\"!", name);
	}

	Application::~Application()
	{
		PG_INFO("Destroying application \"{0}\"!", name);
	}

	void Application::PreInit()
	{
		PG_INFO("Initialising application \"{0}\"!", name);

		window = Window::Create(name);
		window->Init();
	}

	void Application::PostInit()
	{
	}

	void Application::Run()
	{
		PG_INFO("Running application \"{0}!\"", name);

		while (!window->ShouldClose())
		{
			window->InputUpdate();
			window->FrameUpdate();
			window->SwapBuffers();
		}
	}
}