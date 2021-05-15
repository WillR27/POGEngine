#include "POGCorePCH.h"
#include "Application.h"

#include "POGLog.h"

namespace POG::Core
{
	Application::Application(std::string name)
		: window(nullptr)
		, name(name)
		, inputManager()
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
		window->SetEventCallback(POG_BIND_FN(HandleEvent));
	}

	void Application::PostInit()
	{
	}

	void Application::Run()
	{
		POG_INFO("Running application \"{0}!\"", name);

		timer.Reset();
		timer.Start();

		float ups = 10.0f;
		float uInteveral = 1.0f / ups;
		float fps = 20.0f;
		float fInterval = 1.0f / fps;
		
		const int maxUpdatesPerLoop = 10;
		float timeBetweenLoops = 0.0f;
		float timeBetweenUpdates = 0.0f;
		float timeBetweenFrames = 0.0f;

		while (!window->ShouldClose())
		{
			timeBetweenLoops = timer.Stop();
			timer.Reset();
			timer.Start();

			int updatesInCurrentLoop = 0;
			timeBetweenUpdates += timeBetweenLoops;
			timeBetweenFrames += timeBetweenLoops;

			// Try catch up with updates if we are lagging
			while (timeBetweenUpdates >= uInteveral)
			{
				POG_INFO(1.0f / timeBetweenUpdates);

				// Count how many updates we have done this game loop (happens if we are lagging)
				updatesInCurrentLoop++;

				// Check for inputs each update
				window->InputUpdate();

				// Set the remaining lag, if we have updated a lot times without rendering just stop updating
				timeBetweenUpdates = updatesInCurrentLoop >= maxUpdatesPerLoop ? 0.0f : timeBetweenUpdates - uInteveral;
			}

			// Render once every game loop
			if (timeBetweenFrames >= fInterval)
			{
				POG_TRACE(1.0f / timeBetweenFrames);

				window->FrameUpdate();
				window->SwapBuffers();

				// We don't care about trying to catch up with frames so set to 0
				timeBetweenFrames = 0.0f;
			}
		}

		window->Close();
	}

	void Application::HandleEvent(Event& e)
	{
		EventDispatcher ed(e);

		ed.Dispatch<WindowCloseEvent>(POG_BIND_FN(window->HandleWindowCloseEvent));
		ed.Dispatch<WindowSizeEvent>(POG_BIND_FN(window->HandleWindowSizeEvent));
		ed.Dispatch<WindowFocusEvent>(POG_BIND_FN(window->HandleWindowFocusEvent));

		ed.Dispatch<KeyEvent>(POG_BIND_FN(inputManager.HandleKeyEvent));
		ed.Dispatch<MouseMoveEvent>(POG_BIND_FN(inputManager.HandleMouseMoveEvent));
		ed.Dispatch<MouseButtonEvent>(POG_BIND_FN(inputManager.HandleMouseButtonEvent));
	}
}