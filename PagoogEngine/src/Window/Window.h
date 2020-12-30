#pragma once

#include "Event/Event.h"
#include "Event/WindowEvents.h"

namespace PEngine
{
	class Window
	{
	public:
		using EventCallback = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void InputUpdate() = 0;
		virtual void Init() = 0;
		virtual void FrameUpdate() = 0;
		
		virtual void SwapBuffers() = 0;

		virtual bool IsFullscreen() const = 0;
		virtual void SetFullscreen(bool fullscreen) = 0;
		virtual void ToggleFullscreen() = 0;

		virtual bool HandleWindowCloseEvent(WindowCloseEvent& e) = 0;
		virtual bool HandleWindowSizeEvent(WindowSizeEvent& e) = 0;

		virtual void SetEventCallback(EventCallback eventCallback) = 0;

		virtual bool ShouldClose() const = 0;

		static Window* Create();
	};
}

