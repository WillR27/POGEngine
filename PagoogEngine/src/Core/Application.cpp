#include "pgepch.h"
#include "Application.h"

#include "Render/Render.h"

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
		while (!window->ShouldClose())
		{
			window->Update();

			for (Layer* layer : layers)
			{
				layer->Update();
			}

			window->SwapBuffers();
		}
	}

	void Application::HandleEvent(Event& e)
	{
		EventDispatcher ed(e);
		ed.Dispatch<WindowCloseEvent>(PG_BIND_FN(window->HandleWindowCloseEvent));
		ed.Dispatch<WindowSizeEvent>(PG_BIND_FN(window->HandleWindowSizeEvent));
	}

	void Application::AddLayer(Layer* layer)
	{
		layer->Init();
		layers.push_back(layer);
	}
}