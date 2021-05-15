#pragma once

#include "POGCommon.h"

#include "POGCore/Event/InputEvents.h"
#include "POGCore/Event/WindowEvents.h"

namespace POG::Core
{
	struct WindowData
	{
		int width = 0, height = 0;
		bool hasFocus;
		EventCallback eventCallback;
	};

	class Window
	{
	public:
		static std::unique_ptr<Window> Create(std::string name);

		Window(std::string name);

		virtual ~Window() = default;

		virtual void Init() = 0;
		virtual void Close() = 0;

		virtual void InputUpdate() = 0;
		virtual void FrameUpdate() = 0;

		virtual void SwapBuffers() = 0;

		virtual bool HandleWindowCloseEvent(WindowCloseEvent& e) = 0;
		virtual bool HandleWindowSizeEvent(WindowSizeEvent& e) = 0;
		virtual bool HandleWindowFocusEvent(WindowFocusEvent& e) = 0;

		virtual void SetEventCallback(EventCallback eventCallback) = 0;

		virtual bool IsFullscreen() const = 0;
		virtual void SetFullscreen(bool fullscreen) = 0;
		virtual void ToggleFullscreen() = 0;

		virtual bool HasFocus() const = 0;

		virtual bool IsCursorEnabled() const = 0;
		virtual void SetCursorEnabled(bool cursor) = 0;
		virtual void ToggleCursorEnabled() = 0;

		virtual bool ShouldClose() const = 0;

		virtual ContextAddressFunc GetContextAddressFunc() const = 0;

		std::string GetName() const { return name; }

	private:
		std::string name;
	};
}

