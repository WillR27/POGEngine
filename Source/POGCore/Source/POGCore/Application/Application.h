#pragma once

#include "POGCommon.h"

#include "POGCore/Input/InputManager.h"
#include "POGCore/Window/Window.h"

namespace POG::Core
{
	class Application
	{
	public:
		Application(std::string name = "POG Engine");

		virtual ~Application();

		void PreInit();
		virtual void Init() = 0;
		void PostInit();

		void Run();

	protected:
		Common::Timer<Common::Time::Unit::Seconds, float, true> timer;

		InputManager inputManager;

		const Window& GetWindow() { return *window; }

	private:
		std::unique_ptr<Window> window;

		std::string name;

		void HandleEvent(Event& e);
	};

	std::unique_ptr<Application> CreateApplication();
}

