#include "POGCorePCH.h"
#include "Application.h"

#include "POGDebug.h"
#include "POGLog.h"
#include "POGRender.h"

namespace POG::Core
{
	Application* Application::Instance = nullptr;

	Application& Application::GetInstance()
	{
		return *Instance;
	}

	Application::Application(std::string name)
		: name(name)
		, window(nullptr)
		, view()
		, inputManager()
		, activeScene(nullptr)
		, targetUpdatesPerSecond(60.0f)
		, targetUpdateInterval(1.0f / targetUpdatesPerSecond)
		, targetFramesPerSecond(120.0f)
		, targetFrameInterval(1.0f / targetFramesPerSecond)
	{
		POG_ASSERT(Instance == nullptr, "Application already created!");

		POG_INFO("Creating application \"{0}\"!", name);

		Instance = this;
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

		inputManager.AddInputCallback(POG_BIND_FN(Input));

		POG::Render::Render::SetContextAddressFunc(GetWindow().GetContextAddressFunc());
		POG::Render::Render::Init();
	}

	void Application::PostInit()
	{
		activeScene->Init();
	}

	void Application::Run()
	{
		POG_INFO("Running application \"{0}!\"", name);

		timer.Reset();
		timer.Start();
		
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
			while (timeBetweenUpdates >= GetTargetUpdateInterval())
			{
				//POG_INFO(1.0f / timeBetweenUpdates);

				// Count how many updates we have done this game loop (happens if we are lagging)
				updatesInCurrentLoop++;

				// Check for inputs each update
				window->InputUpdate();
				inputManager.Dispatch(GetTargetUpdateInterval());

				activeScene->Update(GetTargetUpdateInterval());

				// Set the remaining lag, if we have updated a lot of times without rendering just stop updating
				timeBetweenUpdates = updatesInCurrentLoop >= maxUpdatesPerLoop ? 0.0f : timeBetweenUpdates - GetTargetUpdateInterval();
			}

			// Render once every game loop
			if (timeBetweenFrames >= GetTargetFrameInterval())
			{
				//POG_TRACE(1.0f / timeBetweenFrames);

				window->FrameUpdate();

				activeScene->FrameUpdate(timeBetweenFrames / GetTargetFrameInterval());

				window->SwapBuffers();

				// We don't care about trying to catch up with frames so set to 0
				timeBetweenFrames = 0.0f;
			}
		}

		activeScene->Exit();

		window->Close();
	}

	void Application::Quit()
	{
		WindowCloseEvent e;
		HandleEvent(e);
	}

	void Application::HandleEvent(Event& e)
	{
		EventDispatcher ed(e);

		ed.Dispatch<WindowCloseEvent>(POG_BIND_FN(window->HandleWindowCloseEvent));
		ed.Dispatch<WindowFocusEvent>(POG_BIND_FN(window->HandleWindowFocusEvent));
		ed.Dispatch<WindowSizeEvent>(POG_BIND_FN(HandleWindowSizeEvent));

		ed.Dispatch<KeyEvent>(POG_BIND_FN(inputManager.HandleKeyEvent));
		ed.Dispatch<MouseMoveEvent>(POG_BIND_FN(inputManager.HandleMouseMoveEvent));
		ed.Dispatch<MouseButtonEvent>(POG_BIND_FN(inputManager.HandleMouseButtonEvent));
	}

	bool Application::HandleWindowSizeEvent(WindowSizeEvent& e)
	{
		POG_INFO(e.ToString());

		view.SetDimensions(e.width, e.height);

		window->UpdateView(view);

		return true;
	}

	void Application::Input(InputPackage& inputPackage, float dt)
	{
	}
}