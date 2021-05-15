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

		virtual void Input(InputPackage& inputPackage, float dt);

		float GetTargetUpdatesPerSecond() const { return targetUpdatesPerSecond; }
		void SetTargetUpdatesPerSecond(float newTarget) { targetUpdatesPerSecond = newTarget; targetUpdateInterval = 1.0f / targetUpdatesPerSecond; }
		
		float GetTargetUpdateInterval() const { return targetUpdateInterval; }
		
		float GetTargetFramesPerSecond() const { return targetFramesPerSecond; }
		void SetTargetFramesPerSecond(float newTarget) { targetFramesPerSecond = newTarget; targetFrameInterval = 1.0f / targetFramesPerSecond; }

		float GetTargetFrameInterval() const { return targetFrameInterval; }

	protected:
		Common::Timer<Common::Time::Unit::Seconds, float, true> timer;

		InputManager inputManager;

		void Quit();

		Window& GetWindow() { return *window; }

	private:
		std::string name;

		std::unique_ptr<Window> window;

		float targetUpdatesPerSecond;
		float targetUpdateInterval;
		float targetFramesPerSecond;
		float targetFrameInterval;

		void HandleEvent(Event& e);
	};

	std::unique_ptr<Application> CreateApplication();
}

