#pragma once

#include "POGCommon.h"

#include "POGCore/Application/Application.h"
#include "POGCore/Event/Events.h"
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

		virtual void TryUpdate(float timeBetweenLoops) = 0;
		virtual void TryFrame(float timeBetweenLoops) = 0;

		virtual void ResetInput() = 0;
		virtual void Input() = 0;
		virtual void Update(float dt) = 0;
		virtual void Frame(float alpha) = 0;

		virtual void SetContextAddressFunc(ContextAddressFunc func) = 0;

		virtual void SetStandalone(bool isStandalone) = 0;
		virtual bool IsStandalone() = 0;

		virtual void SetMainEventBus(EventBus& mainEventBus) = 0;

		virtual Scene& GetActiveScene() = 0;

		// Only used by the editor to check if the client has updated this loop
		virtual bool HasUpdated() const = 0;

		virtual bool IsCursorEnabled() const = 0;
		virtual void SetCursorEnabled(bool isCursorEnabled) = 0;

		virtual float GetTargetUpdatesPerSecond() const = 0;
		virtual float GetTargetFramesPerSecond() const = 0;
	};

	class Application : public IApplication
	{
	public:
		static Application& GetInstance();

		Application(std::string name = "POG Engine");
		Application(const Application&) = delete;
		Application(Application&&) = delete;

		virtual ~Application();

		void Destroy() override;

		void Exit() override;

		void Run() override;

		void PreInit() override;
		void Init() = 0;
		void PostInit() override;

		void TryUpdate(float timeBetweenLoops) override;
		void TryFrame(float timeBetweenLoops) override;

		virtual void Input(InputPackage& inputPackage, float dt);
		void ResetInput() override;
		void Input() override;
		void Update(float dt) override;
		void Frame(float alpha) override;

		void OnCursorEnabledEvent(Core::CursorEnabledEvent& e);
		void OnWindowCloseEvent(WindowCloseEvent& e);

		bool ShouldClose() const { return shouldClose; };

		void SetContextAddressFunc(ContextAddressFunc func) override;

		std::string GetName() const { return name; }

		void SetStandalone(bool isStandalone) override { this->isStandalone = isStandalone; }
		bool IsStandalone() override { return isStandalone; }

		Window& GetWindow() { return *window; }

		const View& GetView() const { return view; }
		int GetWidth() const { return view.GetWidth(); }
		int GetHeight() const { return view.GetHeight(); }

		EventBus& GetMainEventBus() const { return *mainEventBus; }
		void SetMainEventBus(EventBus& mainEventBus) override { this->mainEventBus = &mainEventBus; }

		Scene& GetActiveScene() override { return Scene::GetActiveScene(); }

		InputManager& GetInputManager() { return inputManager; }

		bool HasUpdated() const override { return hasUpdated; }

		bool IsFullscreen() const { return isFullscreen; }
		void SetFullscreen(bool isFullscreen);
		void ToggleFullscreen();

		bool IsCursorEnabled() const override { return isCursorEnabled; }
		void SetCursorEnabled(bool isCursorEnabled) override;
		void ToggleCursorEnabled();

		float GetTargetUpdatesPerSecond() const override { return targetUpdatesPerSecond; }
		void SetTargetUpdatesPerSecond(float newTarget) { targetUpdatesPerSecond = newTarget; targetUpdateInterval = 1.0f / targetUpdatesPerSecond; }
		
		float GetTargetUpdateInterval() const { return targetUpdateInterval; }
		
		float GetTargetFramesPerSecond() const override { return targetFramesPerSecond; }
		void SetTargetFramesPerSecond(float newTarget) { targetFramesPerSecond = newTarget; targetFrameInterval = 1.0f / targetFramesPerSecond; }

		float GetTargetFrameInterval() const { return targetFrameInterval; }

	protected:
		Common::Timer<Common::Time::Unit::Seconds, float, true> timer;

		float timeBetweenLoops;
		float timeBetweenUpdates;
		float timeBetweenFrames;

	private:
		static Application* Instance;

		bool isStandalone;

		std::string name;

		Window* window;
		View view;

		EventBus* mainEventBus;
		InputManager inputManager;

		bool shouldClose;
		bool hasUpdated;

		bool isFullscreen;
		bool isCursorEnabled;

		float targetUpdatesPerSecond;
		float targetUpdateInterval;
		float targetFramesPerSecond;
		float targetFrameInterval;

		void OnWindowSizeEvent(WindowSizeEvent& e);
		void OnMouseMoveEvent(MouseMoveEvent& e);
	};

	Application* CreateApplication();
}