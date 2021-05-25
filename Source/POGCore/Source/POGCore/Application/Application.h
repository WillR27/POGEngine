#pragma once

#include "POGCommon.h"

#include "POGCore/Event/ApplicationEvents.h"
#include "POGCore/Input/InputManager.h"
#include "POGCore/Scene/Scene.h"
#include "POGCore/View/View.h"
#include "POGCore/Window/Window.h"

#include "POGCore/Event/ZEvent.h"

namespace POG::Core
{
	using EditorEventHandler = std::function<bool(Event& e)>;

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

		virtual bool HandleEvent(Event& e) = 0;

		virtual void SetContextAddressFunc(ContextAddressFunc func) = 0;

		virtual void SetStandalone(bool isStandalone) = 0;
		virtual bool IsStandalone() = 0;

		virtual void SetEditorEventHandler(EditorEventHandler editorEventHandler) = 0;

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

		bool HandleEvent(Event& e) override;

		virtual bool HandleCursorEnabledEvent(Core::CursorEnabledEvent& e);

		EventBus mainBus;
		void HandleZWindowCloseEvent(ZWindowCloseEvent& e);

		bool ShouldClose() const { return shouldClose; };

		void SetContextAddressFunc(ContextAddressFunc func) override;

		std::string GetName() const { return name; }

		void SetStandalone(bool isStandalone) override { this->isStandalone = isStandalone; }
		bool IsStandalone() override { return isStandalone; }

		Window& GetWindow() { return *window; }

		const View& GetView() const { return view; }
		int GetWidth() const { return view.GetWidth(); }
		int GetHeight() const { return view.GetHeight(); }

		InputManager& GetInputManager() { return inputManager; }

		void SetEditorEventHandler(EditorEventHandler editorEventHandler) override { this->editorEventHandler = editorEventHandler; }

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

		InputManager inputManager;

		EditorEventHandler editorEventHandler;
		bool ignoreNextEvent;

		bool shouldClose;
		bool hasUpdated;

		bool isFullscreen;
		bool isCursorEnabled;

		float targetUpdatesPerSecond;
		float targetUpdateInterval;
		float targetFramesPerSecond;
		float targetFrameInterval;

		bool HandleWindowSizeEvent(WindowSizeEvent& e);
		bool HandleMouseMoveEvent(MouseMoveEvent& e);
	};

	Application* CreateApplication();
}