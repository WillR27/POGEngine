#include "POGCorePCH.h"
#include "Application.h"

#include "POGCore/Scene/Scene.h"

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
		, isStandalone(true)
		, view(1200, 800)
		, mainEventBus(nullptr)
		, inputManager()
		, shouldClose(false)
		, hasUpdated(false)
		, isFullscreen(false)
		, isCursorEnabled(true)
		, targetUpdatesPerSecond(30.0f)
		, targetUpdateInterval(1.0f / targetUpdatesPerSecond)
		, targetFramesPerSecond(60.0f)
		, targetFrameInterval(1.0f / targetFramesPerSecond)
		, timeBetweenLoops(0)
		, timeBetweenUpdates(0)
		, timeBetweenFrames(0)
	{
		//POG_ASSERT(Instance == nullptr, "Application already created!");
		POG::Log::Log::Init();
		POG_INFO("Creating application \"{0}\"!", name);

		if (!Instance)
		{
			Instance = this;
		}
	}

	Application::~Application()
	{
		POG_INFO("Destroying application \"{0}\"!", name);

		if (IsStandalone())
		{
			delete window;
			delete mainEventBus;
		}
	}

	void Application::Destroy()
	{
		delete this;
	}

	void Application::Exit()
	{
		POG_INFO("Exiting application \"{0}\"!", name);

		GetMainEventBus().Unsubscribe(this, &Application::OnWindowCloseEvent);
		GetMainEventBus().Unsubscribe(this, &Application::OnCursorEnabledEvent);
		
		if (IsStandalone())
		{
			GetMainEventBus().Unsubscribe(window, &Window::OnWindowFocusEvent);
			GetMainEventBus().Unsubscribe(this, &Application::OnWindowSizeEvent);
		}

		GetMainEventBus().Unsubscribe(inputManager, &InputManager::OnKeyEvent);
		GetMainEventBus().Unsubscribe(inputManager, &InputManager::OnMouseButtonEvent);
		GetMainEventBus().Unsubscribe(this, &Application::OnMouseMoveEvent);

		// This only applies to a standalone app that is run via Run()
		// In the editor Run() is never used
		if (IsStandalone())
		{
			shouldClose = true;
		}
	}

	void Application::PreInit()
	{
		POG_INFO("Initialising application \"{0}\"!", name);

		if (IsStandalone())
		{
			mainEventBus = new EventBus();

			window = Window::Create(name);
			window->Init();

			Render::SetContextAddressFunc(GetWindow().GetContextAddressFunc());
			Render::Init();
		}

		GetMainEventBus().Subscribe(this, &Application::OnWindowCloseEvent);
		GetMainEventBus().Subscribe(this, &Application::OnCursorEnabledEvent);

		if (IsStandalone())
		{
			GetMainEventBus().Subscribe(window, &Window::OnWindowFocusEvent);
			GetMainEventBus().Subscribe(this, &Application::OnWindowSizeEvent);
		}

		GetMainEventBus().Subscribe(inputManager, &InputManager::OnKeyEvent);
		GetMainEventBus().Subscribe(inputManager, &InputManager::OnMouseButtonEvent);
		GetMainEventBus().Subscribe(this, &Application::OnMouseMoveEvent);

		inputManager.AddInputCallback(POG_BIND_FN_THIS(Input));
	}

	void Application::PostInit()
	{
		Scene::GetActiveScene().PreInit();
		Scene::GetActiveScene().Init();
		Scene::GetActiveScene().PostInit();

		inputManager.AddInputCallback(POG_BIND_FN(Scene::GetActiveScene().Input));
	}

	void Application::TryUpdate(float timeBetweenLoops)
	{
		hasUpdated = false;

		timeBetweenUpdates += timeBetweenLoops;

		if (IsStandalone())
		{
			const int maxUpdatesPerLoop = 10;
			int updatesInCurrentLoop = 0;

			// Try catch up with updates if we are lagging
			while (timeBetweenUpdates >= GetTargetUpdateInterval())
			{
				//POG_INFO(1.0f / timeBetweenUpdates);

				// Count how many updates we have done this game loop (happens if we are lagging)
				updatesInCurrentLoop++;

				Update(GetTargetUpdateInterval());

				// Set the remaining lag, if we have updated a lot of times without rendering just stop updating
				timeBetweenUpdates = updatesInCurrentLoop >= maxUpdatesPerLoop ? 0.0f : timeBetweenUpdates - GetTargetUpdateInterval();
			}
		}
		else
		{
			if (timeBetweenUpdates >= GetTargetUpdateInterval())
			{
				Update(GetTargetUpdateInterval());

				// If we are in the editor, don't try to catch up
				timeBetweenUpdates = 0.0f;
			}
		}
	}

	void Application::TryFrame(float timeBetweenLoops)
	{
		timeBetweenFrames += timeBetweenLoops;

		// Render once every game loop
		if (timeBetweenFrames >= GetTargetFrameInterval())
		{
			//POG_TRACE(1.0f / timeBetweenFrames);

			Frame(timeBetweenFrames / GetTargetFrameInterval());

			// We don't care about trying to catch up with frames so set to 0
			timeBetweenFrames = 0.0f;
		}
	}

	void Application::Input(InputPackage& inputPackage, float dt)
	{
	}

	void Application::ResetInput()
	{
		Input::ResetMouseDeltas();
	}

	void Application::Input()
	{
		if (IsStandalone())
		{
			ResetInput();

			// Check for inputs each update
			window->Input();
		}
	}

	void Application::Update(float dt)
	{
		hasUpdated = true;

		Input();

		inputManager.Dispatch(dt);

		Scene::GetActiveScene().Update(dt);
	}

	void Application::Frame(float alpha)
	{
		if (IsStandalone())
		{
			window->Frame();
		}

		Scene::GetActiveScene().Frame(timeBetweenFrames / GetTargetFrameInterval());

		if (IsStandalone())
		{
			window->SwapBuffers();
		}
	}

	void Application::Run()
	{
		POG_INFO("Running application \"{0}!\"", name);

		PreInit();
		Init();
		PostInit();

		timer.Reset();
		timer.Start();

		while (!ShouldClose())
		{
			timeBetweenLoops = timer.Stop();
			timer.Reset();
			timer.Start();

			TryUpdate(timeBetweenLoops);
			TryFrame(timeBetweenLoops);
		}

		Scene::GetActiveScene().Exit();

		window->Close();
	}

	void Application::OnCursorEnabledEvent(Core::CursorEnabledEvent& e)
	{
		isCursorEnabled = e.isCursorEnabled;

		if (IsStandalone())
		{
			window->SetCursorEnabled(isCursorEnabled);
		}
	}

	void Application::OnWindowCloseEvent(WindowCloseEvent& e)
	{
		Exit();

		e.SetHandled();
	}

	void Application::SetContextAddressFunc(ContextAddressFunc func)
	{
		Render::SetContextAddressFunc(func);
	}

	void Application::SetFullscreen(bool isFullscreen)
	{
		if (IsStandalone())
		{
			this->isFullscreen = isFullscreen;

			if (IsStandalone())
			{
				window->SetFullscreen(isFullscreen);
			}
		}
	}

	void Application::ToggleFullscreen()
	{
		SetFullscreen(!IsFullscreen());
	}

	void Application::SetCursorEnabled(bool isCursorEnabled)
	{
		GetMainEventBus().Publish(CursorEnabledEvent(isCursorEnabled));
	}

	void Application::ToggleCursorEnabled()
	{
		SetCursorEnabled(!IsCursorEnabled());
	}

	void Application::OnWindowSizeEvent(WindowSizeEvent& e)
	{
		POG_INFO(e.ToString());

		view.SetDimensions(e.width, e.height);

		if (IsStandalone())
		{
			window->UpdateView(view);
		}

		e.SetHandled();
	}

	void Application::OnMouseMoveEvent(MouseMoveEvent& e)
	{
		Input::SetMouseXY(e.mouseX, e.mouseY);

		inputManager.OnMouseMoveEvent(e);
	}
}

extern "C" __declspec(dllexport) POG::Core::IApplication* __cdecl CreateClientApplication()
{
	return POG::Core::CreateApplication();
}