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
		, view()
		, mainEventBus(nullptr)
		, inputManager()
		, shouldClose(false)
		, hasUpdated(false)
		, editorEventHandler()
		, ignoreNextEvent(false)
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

		GetMainEventBus().Unsubscribe(this, &Application::HandleWindowCloseEvent);
		GetMainEventBus().Unsubscribe(this, &Application::HandleCursorEnabledEvent);

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
			window->SetEventCallback(POG_BIND_FN_THIS(HandleEvent));

			Render::SetContextAddressFunc(GetWindow().GetContextAddressFunc());
			Render::Init();
		}

		GetMainEventBus().Subscribe(this, &Application::HandleWindowCloseEvent);
		GetMainEventBus().Subscribe(this, &Application::HandleCursorEnabledEvent);

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

	bool Application::HandleEvent(Event& e)
	{
		if (!ignoreNextEvent)
		{
			EventDispatcher ed(e);

			if (editorEventHandler)
			{
				// Send event to editor but make sure we don't get stuck in an infinite loop
				ignoreNextEvent = true;
				ed.Dispatch<Event>(POG_BIND_FN_THIS(editorEventHandler));
				ignoreNextEvent = false;
			}

			if (IsStandalone())
			{
				ed.Dispatch<WindowFocusEvent>(POG_BIND_FN_THIS(window->HandleWindowFocusEvent));
				ed.Dispatch<WindowSizeEvent>(POG_BIND_FN_THIS(HandleWindowSizeEvent));
			}

			ed.Dispatch<KeyEvent>(POG_BIND_FN_THIS(inputManager.HandleKeyEvent));
			ed.Dispatch<MouseMoveEvent>(POG_BIND_FN_THIS(HandleMouseMoveEvent));
			ed.Dispatch<MouseButtonEvent>(POG_BIND_FN_THIS(inputManager.HandleMouseButtonEvent));

			ed.Dispatch<Event>(POG_BIND_FN(Scene::GetActiveScene().HandleEvent));
		}

		return false;
	}

	void Application::HandleCursorEnabledEvent(Core::CursorEnabledEvent& e)
	{
		isCursorEnabled = e.isCursorEnabled;

		if (IsStandalone())
		{
			window->SetCursorEnabled(isCursorEnabled);
		}
	}

	void Application::HandleWindowCloseEvent(WindowCloseEvent& e)
	{
		Exit();
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
		GetMainEventBus().Publish(new CursorEnabledEvent(isCursorEnabled));
	}

	void Application::ToggleCursorEnabled()
	{
		SetCursorEnabled(!IsCursorEnabled());
	}

	bool Application::HandleWindowSizeEvent(WindowSizeEvent& e)
	{
		POG_INFO(e.ToString());

		view.SetDimensions(e.width, e.height);

		if (IsStandalone())
		{
			window->UpdateView(view);
		}

		return true;
	}

	bool Application::HandleMouseMoveEvent(MouseMoveEvent& e)
	{
		Input::SetMouseXY(e.mouseX, e.mouseY);

		inputManager.HandleMouseMoveEvent(e);

		return false;
	}
}

extern "C" __declspec(dllexport) POG::Core::IApplication* __cdecl CreateClientApplication()
{
	return POG::Core::CreateApplication();
}