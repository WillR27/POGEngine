#pragma once

#include "POGCommon.h"

#include "POGCore/Event/InputEvents.h"
#include "POGCore/Event/WindowEvents.h"
#include "POGCore/View/View.h"

namespace POG::Core
{
	struct WindowData
	{
		int width = 0, height = 0;
		bool hasFocus;
	};

	class Window
	{
	public:
		static Window* Create(std::string name);

		Window(std::string name);

		virtual ~Window() = default;

		virtual void Init() = 0;
		virtual void Close() = 0;

		virtual void Input() = 0;
		virtual void Frame() = 0;

		virtual void SwapBuffers() = 0;

		virtual void OnWindowFocusEvent(WindowFocusEvent& e) = 0;

		virtual void UpdateView(View view) = 0;

		virtual bool IsFullscreen() const = 0;
		virtual void SetFullscreen(bool isFullscreen) = 0;

		virtual bool HasFocus() const = 0;

		virtual bool IsCursorEnabled() const = 0;
		virtual void SetCursorEnabled(bool isCursorEnabled) = 0;

		virtual ContextAddressFunc GetContextAddressFunc() const = 0;

		virtual void* GetActualWindow() = 0;

		std::string GetName() const { return name; }

	private:
		std::string name;
	};
}

