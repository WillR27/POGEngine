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

		Render::Init();
	}

	void Application::Run()
	{
		Time::Reset();

		double deltaTime;

		while (!window->ShouldClose())
		{
			deltaTime = Time::DeltaTime();

			Time::DeltaTimeUpdate += deltaTime;
			while (Time::DeltaTimeUpdate > Time::TimeUntilUpdate)
			{
				window->InputUpdate();

				for (Layer* layer : layers)
				{
					layer->InputUpdate(Time::TimeUntilUpdate);
				}

				for (Layer* layer : layers)
				{
					layer->Update(Time::TimeUntilUpdate);
				}

				Time::DeltaTimeUpdate -= Time::TimeUntilUpdate;
			}

			Time::DeltaTimeFrame += deltaTime;
			if (Time::DeltaTimeFrame > Time::TimeUntilFrame)
			{
				window->FrameUpdate();

				for (Layer* layer : layers)
				{
					layer->FrameUpdate(Time::DeltaTimeFrame);
				}

				window->SwapBuffers();

				Time::DeltaTimeFrame = 0.0f;
			}
		}
	}

	void Application::HandleEvent(Event& e)
	{
		EventDispatcher ed(e);
		ed.Dispatch<WindowCloseEvent>(PG_BIND_FN(window->HandleWindowCloseEvent));
		ed.Dispatch<WindowSizeEvent>(PG_BIND_FN(window->HandleWindowSizeEvent));

		for (Layer* layer : layers)
		{
			if (e.IsHandled())
			{
				break;
			}

			layer->HandleEvent(e);
		}
	}

	void Application::AddLayer(Layer* layer)
	{
		layer->Init();
		layers.push_back(layer);
	}
}