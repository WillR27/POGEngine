#pragma once

#include "POGCommon.h"

#include "POGCore/Input/InputManager.h"
#include "POGCore/Scene/Scene.h"
#include "POGCore/View/View.h"
#include "POGCore/Window/Window.h"

namespace POG::Core
{
	class Application
	{
	public:
		static Application& GetInstance();

		Window* window;

		Application(std::string name = "POG Engine");

		virtual ~Application();

		void PreInit();
		virtual void Init() = 0;
		void PostInit();

		void Run();

		virtual void Loop();

		void Quit();

		void HandleEvent(Event& e);

		virtual void Input(InputPackage& inputPackage, float dt);

		bool ShouldClose() const { return shouldClose; };

		float GetTargetUpdatesPerSecond() const { return targetUpdatesPerSecond; }
		void SetTargetUpdatesPerSecond(float newTarget) { targetUpdatesPerSecond = newTarget; targetUpdateInterval = 1.0f / targetUpdatesPerSecond; }
		
		float GetTargetUpdateInterval() const { return targetUpdateInterval; }
		
		float GetTargetFramesPerSecond() const { return targetFramesPerSecond; }
		void SetTargetFramesPerSecond(float newTarget) { targetFramesPerSecond = newTarget; targetFrameInterval = 1.0f / targetFramesPerSecond; }

		float GetTargetFrameInterval() const { return targetFrameInterval; }

		const View& GetView() const { return view; }
		int GetWidth() const { return view.GetWidth(); }
		int GetHeight() const { return view.GetHeight(); }

	protected:
		Common::Timer<Common::Time::Unit::Seconds, float, true> timer;

		InputManager inputManager;

		std::unique_ptr<Scene> activeScene;

		Window& GetWindow() { return *window; }

	private:
		static Application* Instance;

		std::string name;

		View view;

		bool shouldClose;

		float targetUpdatesPerSecond;
		float targetUpdateInterval;
		float targetFramesPerSecond;
		float targetFrameInterval;

		float timeBetweenLoops;
		float timeBetweenUpdates;
		float timeBetweenFrames;

		bool HandleWindowSizeEvent(WindowSizeEvent& e);
	};

	std::unique_ptr<Application> CreateApplication();
}

