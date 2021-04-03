#include "POGCorePCH.h"
#include "Application.h"

#include "POGLog.h"

namespace POG::Core
{
	Application::Application(std::string name)
		: window(nullptr)
		, name(name)
	{
		POG_INFO("Creating application \"{0}\"!", name);
	}

	Application::~Application()
	{
		POG_INFO("Destroying application \"{0}\"!", name);
	}

	void Application::PreInit()
	{
		POG_INFO("Initialising application \"{0}\"!", name);

		window = Window::Create(name);
		window->Init();
	}

	void Application::PostInit()
	{
	}

	void Application::Run()
	{
		POG_INFO("Running application \"{0}!\"", name);

		while (!window->ShouldClose())
		{
			window->InputUpdate();
			window->FrameUpdate();
			window->SwapBuffers();
		}
	}
}