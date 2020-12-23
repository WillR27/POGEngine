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

		delete window;
	}

	void Application::Init()
	{
		PG_INFO("Initialising application!");

		window = Window::Create();
		window->Init();
		window->SetEventCallback(PG_BIND_FN(HandleEvent));

		inputManager.AddInputPackageCallback(PG_BIND_FN(ActionCallback));

		Render::Init();
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
			while (deltaTimeUpdate > Time::TimeUntilUpdate)
			{
				window->InputUpdate();
				inputManager.Send(deltaTimeUpdate);

				for (Layer* layer : layers)
				{
					layer->InputUpdate(Time::TimeUntilUpdate);
				}

				for (Layer* layer : layers)
				{
					layer->Update(Time::TimeUntilUpdate);
				}

				deltaTimeUpdate -= Time::TimeUntilUpdate;
			}

			deltaTimeFrame += deltaTime;
			if (deltaTimeFrame > Time::TimeUntilFrame)
			{
				window->FrameUpdate();

				for (Layer* layer : layers)
				{
					layer->FrameUpdate(deltaTimeFrame);
				}

				window->SwapBuffers();

				deltaTimeFrame = 0.0f;
			}
		}
	}

	void Application::HandleEvent(Event& e)
	{
		EventDispatcher ed(e);
		ed.Dispatch<WindowCloseEvent>(PG_BIND_FN(window->HandleWindowCloseEvent));
		ed.Dispatch<WindowSizeEvent>(PG_BIND_FN(window->HandleWindowSizeEvent));
		ed.Dispatch<KeyEvent>(PG_BIND_FN(inputManager.HandleKeyEvent));

		for (Layer* layer : layers)
		{
			if (e.IsHandled())
			{
				break;
			}

			layer->HandleEvent(e);
		}
	}

	void Application::ActionCallback(InputPackage& inputPackage, float dt)
	{
	}

	void Application::AddLayer(Layer* layer)
	{
		layer->Init();
		layers.push_back(layer);
	}
}