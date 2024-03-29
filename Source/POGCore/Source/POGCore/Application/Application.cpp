#include "POGCorePCH.h"
#include "Application.h"

#include "POGDebug.h"
#include "POGGraphics.h"
#include "POGLog.h"

#include "POGCore/Graphics/MeshManager.h"
#include "POGCore/Graphics/ShaderManager.h"
#include "POGCore/Graphics/TextureManager.h"
#include "POGCore/Scene/Scene.h"

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
		, shouldClose(false)
		, hasUpdated(false)
		, isFullscreen(false)
		, isCursorEnabled(true)
		, targetUpdatesPerSecond(30.0f)
		, targetUpdateInterval(1.0f / targetUpdatesPerSecond)
		, targetFramesPerSecond(60.0f)
		, targetFrameInterval(1.0f / targetFramesPerSecond)
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

		GetMainEventBus().Unsubscribe(&Application::OnWindowCloseEvent, this);
		GetMainEventBus().Unsubscribe(&Application::OnCursorEnabledEvent, this);
		
		if (IsStandalone())
		{
			GetMainEventBus().Unsubscribe(&Window::OnWindowFocusEvent, window);
			GetMainEventBus().Unsubscribe(&Application::OnWindowSizeEvent, this);
		}

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

			Graphics::SetContextAddressFunc(GetWindow().GetContextAddressFunc());
			Graphics::Init();
		}

		Keyboard::Init();
		Mouse::Init();

		MeshManager::Init();
		ShaderManager::Init();
		TextureManager::Init();

		GetMainEventBus().Subscribe(&Application::OnWindowCloseEvent, this);
		GetMainEventBus().Subscribe(&Application::OnCursorEnabledEvent, this);

		if (IsStandalone())
		{
			GetMainEventBus().Subscribe(&Window::OnWindowFocusEvent, window);
			GetMainEventBus().Subscribe(&Application::OnWindowSizeEvent, this);
		}

		Input::AddInputCallback(&Application::Input, this);
	}

	void Application::PostInit()
	{
		Scene::GetActiveScene().PreInit();
		Scene::GetActiveScene().Init();
		Scene::GetActiveScene().PostInit();

		Input::AddInputCallback(&Scene::Input, &Scene::GetActiveScene());
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
				//POG_WARN(timeBetweenUpdates);

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

			Frame(timeBetweenUpdates / GetTargetUpdateInterval());

			// We don't care about trying to catch up with frames so set to 0
			timeBetweenFrames = 0.0f;
		}
	}

	void Application::Input(InputPackage& inputPackage, float dt)
	{
	}

	void Application::ResetInput()
	{
		Keyboard::ResetKeys();
		Mouse::ResetDeltas();
		Mouse::ResetButtons();
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

		Scene::GetActiveScene().PreInput();

		Input::Dispatch(dt);

		Scene::GetActiveScene().PreUpdate(dt);
		Scene::GetActiveScene().Update(dt);
		Scene::GetActiveScene().PostUpdate(dt);
	}

	void Application::Frame(float alpha)
	{
		if (IsStandalone())
		{
			window->Frame();
		}

		Scene::GetActiveScene().PreFrame(alpha);
		Scene::GetActiveScene().Frame(alpha);
		Scene::GetActiveScene().PostFrame(alpha);

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

		// Call an initial update to kick things off
		Update(0.0f);

		while (!ShouldClose())
		{
			float timeBetweenLoops = timer.Stop();
			timer.Reset();
			timer.Start();

			// If the app runs too fast, the timer is not accurate enough in seconds as a float
			// So if we are running at over 1000 loops per second, just create a hard limit
			if (timeBetweenLoops < 0.001f)
			{
				Sleep(1);
			}
		
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
		Graphics::SetContextAddressFunc(func);
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

		Graphics::SetWindowWidthHeight(static_cast<float>(e.width), static_cast<float>(e.height));

		if (IsStandalone())
		{
			window->UpdateView(view);
		}

		e.SetHandled();
	}
}

extern "C" __declspec(dllexport) POG::Core::IApplication* __cdecl CreateClientApplication()
{
	return POG::Core::CreateApplication();
}