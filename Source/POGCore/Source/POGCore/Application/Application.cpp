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
		, isStandalone(true)
		, view()
		, inputManager(nullptr)
		, activeScene(nullptr)
		, shouldClose(false)
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
			delete inputManager;
			delete window;
		}
	}

	void Application::Destroy()
	{
		delete this;
	}

	void Application::Exit()
	{
		POG_INFO("Exiting application \"{0}\"!", name);

		shouldClose = true;
	}

	void Application::PreInit()
	{
		POG_INFO("Initialising application \"{0}\"!", name);

		if (IsStandalone())
		{
			window = Window::Create(name);
			window->Init();
			window->SetEventCallback(POG_BIND_FN(HandleEvent));

			Render::SetContextAddressFunc(GetWindow().GetContextAddressFunc());
			Render::Init();

			inputManager = new InputManager();
		}

		inputManager->AddInputCallback(POG_BIND_FN(Input));
	}

	void Application::PostInit()
	{
		activeScene->Init();

		inputManager->AddInputCallback(POG_BIND_FN(activeScene->Input));

		timer.Reset();
		timer.Start();
	}

	void Application::Input(InputPackage& inputPackage, float dt)
	{
	}

	void Application::Update(float dt)
	{
		if (IsStandalone())
		{
			// Check for inputs each update
			window->Input();
		}
		
		inputManager->Dispatch(dt);

		activeScene->Update(dt);
	}

	void Application::Frame(float alpha)
	{
		if (IsStandalone())
		{
			window->Frame();
		}

		activeScene->Frame(timeBetweenFrames / GetTargetFrameInterval());

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

		while (!ShouldClose())
		{
			Loop();
		}

		activeScene->Exit();

		window->Close();
	}

	void Application::Loop()
	{
		const int maxUpdatesPerLoop = 10;

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

			Update(GetTargetUpdateInterval());

			// Set the remaining lag, if we have updated a lot of times without rendering just stop updating
			timeBetweenUpdates = updatesInCurrentLoop >= maxUpdatesPerLoop ? 0.0f : timeBetweenUpdates - GetTargetUpdateInterval();
		}

		// Render once every game loop
		if (timeBetweenFrames >= GetTargetFrameInterval())
		{
			//POG_TRACE(1.0f / timeBetweenFrames);

			Frame(timeBetweenFrames / GetTargetFrameInterval());

			// We don't care about trying to catch up with frames so set to 0
			timeBetweenFrames = 0.0f;
		}
	}

	void Application::HandleEvent(Event& e)
	{
		EventDispatcher ed(e);

		if (IsStandalone())
		{
			ed.Dispatch<WindowCloseEvent>(POG_BIND_FN(window->HandleWindowCloseEvent));
			ed.Dispatch<WindowFocusEvent>(POG_BIND_FN(window->HandleWindowFocusEvent));
			ed.Dispatch<WindowSizeEvent>(POG_BIND_FN(HandleWindowSizeEvent));
		}

		ed.Dispatch<KeyEvent>(POG_BIND_FN(inputManager->HandleKeyEvent));
		ed.Dispatch<MouseMoveEvent>(POG_BIND_FN(inputManager->HandleMouseMoveEvent));
		ed.Dispatch<MouseButtonEvent>(POG_BIND_FN(inputManager->HandleMouseButtonEvent));
	}

	void Application::SetContextAddressFunc(ContextAddressFunc func)
	{
		Render::SetContextAddressFunc(func);
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
}

extern "C" __declspec(dllexport) POG::Core::IApplication * __cdecl CreateClientApplication()
{
	return POG::Core::CreateApplication();
}