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

		virtual void Init() = 0;
		virtual void Update() = 0;
		
		virtual void SwapBuffers() = 0;

		virtual bool HandleWindowCloseEvent(WindowCloseEvent& e) = 0;
		virtual bool HandleWindowSizeEvent(WindowSizeEvent& e) = 0;

		virtual void SetEventCallback(EventCallback eventCallback) = 0;

		virtual bool ShouldClose() const = 0;

		static Window* Create();
	};
}

