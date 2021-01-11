#pragma once

#include "Window.h"

#include <GLFW/glfw3.h>

namespace PEngine
{
	class WindowsWindow : public Window
	{
	public:
		struct WindowData
		{
			int width = 0, height = 0;
			Window::EventCallback eventCallback;
		};

		WindowsWindow();
		virtual ~WindowsWindow();

		virtual void InputUpdate() override;
		virtual void Init() override;
		virtual void FrameUpdate() override;

		virtual void SwapBuffers() override;

		virtual bool IsFullscreen() const override;
		virtual void SetFullscreen(bool fullscreen) override;
		virtual void ToggleFullscreen() override;

		virtual bool HasCursor() const override;
		virtual void SetCursorMode(bool cursor) override;
		virtual void ToggleCursorMode() override;

		virtual bool HandleWindowCloseEvent(WindowCloseEvent& e) override;
		virtual bool HandleWindowSizeEvent(WindowSizeEvent& e) override;

		virtual void SetEventCallback(EventCallback eventCallback) override;

		virtual bool ShouldClose() const override;

	private:
		WindowData windowData;

		GLFWwindow* window;

		bool shouldClose;
		bool fullscreen;
		bool cursor;

		void InitWindow();
		void InitCallbacks();

		void Close();

		static WindowData& GetWindowData(GLFWwindow* window);
	};
}

