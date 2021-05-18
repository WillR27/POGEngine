#pragma once

#include "POGCommon.h"

#include "POGCore/Input/InputManager.h"
#include "POGCore/Scene/Scene.h"
#include "POGCore/View/View.h"
#include "POGCore/Window/Window.h"

namespace POG::Core
{
	class IApplication
	{
	public:
		virtual void Destroy() = 0;

		virtual void Exit() = 0;

		virtual void Run() = 0;

		virtual void PreInit() = 0;
		virtual void Init() = 0;
		virtual void PostInit() = 0;

		virtual void Update(float dt) = 0;
		virtual void Frame(float alpha) = 0;

		virtual void SetContextAddressFunc(ContextAddressFunc func) = 0;
	};

	class Application : public IApplication
	{
	public:
		static Application& GetInstance();

		Window* window;
		bool ownWindow;
		InputManager* inputManager;

		Application(std::string name = "POG Engine");

		virtual ~Application();

		void Destroy() override;

		void Exit() override;

		void Run() override;

		void PreInit() override;
		void Init() = 0;
		void PostInit() override;

		virtual void Input(InputPackage& inputPackage, float dt);
		void Update(float dt) override;
		void Frame(float alpha) override;

		virtual void Loop();

		void HandleEvent(Event& e);

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

		void SetContextAddressFunc(ContextAddressFunc func) override;

	protected:
		Common::Timer<Common::Time::Unit::Seconds, float, true> timer;

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

	Application* CreateApplication();
}