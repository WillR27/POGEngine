#pragma once

#include <GLFW/glfw3.h>

#include "Window.h"

namespace PEngine
{
	class WindowsWindow : public Window
	{
	public:
		struct WindowData
		{
			int width = 0, height = 0;
			bool hasFocus;
			Window::EventCallback eventCallback;
		};

		WindowsWindow();
		virtual ~WindowsWindow();

		virtual void InputUpdate() override;
		virtual void Init() override;
		virtual void FrameUpdate() override;

		virtual void SwapBuffers() override;

		virtual bool IsFullscreen() const override { return fullscreen; }
		virtual void SetFullscreen(bool fullscreen) override;
		virtual void ToggleFullscreen() override;

		virtual bool HasFocus() const override { return hasFocus; }

		virtual bool HasCursor() const override { return cursor; }
		virtual void SetCursorMode(bool cursor) override;
		virtual void ToggleCursorMode() override;

		virtual bool HandleWindowCloseEvent(WindowCloseEvent& e) override;
		virtual bool HandleWindowSizeEvent(WindowSizeEvent& e) override;
		virtual bool HandleWindowFocusEvent(WindowFocusEvent& e) override;

		virtual void SetEventCallback(EventCallback eventCallback) override;

		virtual bool ShouldClose() const override { return shouldClose; }

	private:
		WindowData windowData;

		GLFWwindow* window;

		bool shouldClose;
		bool fullscreen;
		bool hasFocus;
		bool cursor;

		void InitWindow();
		void InitCallbacks();

		void Close();

		static WindowData& GetWindowData(GLFWwindow* window);
	};
}

