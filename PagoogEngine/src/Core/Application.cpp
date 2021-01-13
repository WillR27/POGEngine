#include "pgepch.h"
#include "Application.h"

#include "Time.h"

#include "Event/InputEvents.h"
#include "Render/Core/Render.h"
#include "Input/Input.h"

namespace PEngine
{
	Application::Application()
		: window(nullptr)
		, inputManager()
	{
		PG_INFO("Creating application!");
	}

	Application::~Application()
	{
		PG_INFO("Destroying application!");

		for (Scene* scene : scenes)
		{
			delete scene;
		}

		delete window;
	}

	void Application::PreInit()
	{
		PG_INFO("Initialising application!");

		window = Window::Create();
		window->Init();
		window->SetEventCallback(PG_BIND_FN(HandleEvent));
		window->SetCursorMode(false);

		inputManager.AddInputPackageCallback(PG_BIND_FN(ActionCallback));

		Render::Init();
	}

	void Application::PostInit()
	{
		Scene::ActiveScene->Init();
	}

	void Application::Run()
	{
		Time::Reset();

		float deltaTime;
		float deltaTimeUpdate = 0.0f;
		float deltaTimeFrame = 0.0f;

		while (!window->ShouldClose())
		{
			deltaTime = Time::DeltaTime();

			deltaTimeUpdate += deltaTime;

			float spiralOfDeathPreventer = 1.0f;
			while (deltaTimeUpdate >= Time::TimeUntilUpdate)
			{
				//PG_TRACE((1.0f / deltaTimeUpdate));
				window->InputUpdate();
				inputManager.Send(deltaTimeUpdate);

				Scene::ActiveScene->Update(Time::TimeUntilUpdate);
				
				deltaTimeUpdate -= (Time::TimeUntilUpdate * spiralOfDeathPreventer);

				spiralOfDeathPreventer += 0.2f;
			}

			if (window->HasFocus() || !window->IsFullscreen())
			{
				deltaTimeFrame += deltaTime;
				if (deltaTimeFrame >= Time::TimeUntilFrame)
				{
					//PG_WARN((1.0f / deltaTimeFrame));
					window->FrameUpdate();

					Scene::ActiveScene->FrameUpdate(deltaTimeUpdate / Time::TimeUntilUpdate);

					window->SwapBuffers();

					deltaTimeFrame = 0.0f;
				}
			}
		}
	}

	void Application::HandleEvent(Event& e)
	{
		EventDispatcher ed(e);

		ed.Dispatch<WindowCloseEvent>(PG_BIND_FN(window->HandleWindowCloseEvent));
		ed.Dispatch<WindowSizeEvent>(PG_BIND_FN(window->HandleWindowSizeEvent));
		ed.Dispatch<WindowFocusEvent>(PG_BIND_FN(window->HandleWindowFocusEvent));

		ed.Dispatch<KeyEvent>(PG_BIND_FN(inputManager.HandleKeyEvent));
		ed.Dispatch<MouseMoveEvent>(PG_BIND_FN(inputManager.HandleMouseMoveEvent));
		ed.Dispatch<MouseButtonEvent>(PG_BIND_FN(inputManager.HandleMouseButtonEvent));

		if (!e.IsHandled())
		{
			Scene::ActiveScene->HandleEvent(e);
		}
	}

	void Application::ActionCallback(InputPackage& inputPackage, float dt)
	{
	}

	void Application::AddScene(Scene* scene)
	{
		scenes.push_back(scene);
		Scene::ActiveScene = scene;
	}
}