#pragma once

#include "PagoogCommon.h"

#include "Window.h"

// If we include GLFW inside this header then we get APIENTRY redefinitions
struct GLFWwindow;

namespace Pagoog::Core
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(std::string name);

		virtual ~WindowsWindow();

		virtual void Init() override;

		virtual void InputUpdate() override;
		virtual void FrameUpdate() override;

		virtual void SwapBuffers() override;

		virtual bool HandleWindowCloseEvent(WindowCloseEvent& e) override;
		virtual bool HandleWindowSizeEvent(WindowSizeEvent& e) override;
		virtual bool HandleWindowFocusEvent(WindowFocusEvent& e) override;

		virtual void SetEventCallback(EventCallback eventCallback) override;

		virtual bool IsFullscreen() const override { return isFullscreen; }
		virtual void SetFullscreen(bool fullscreen) override;
		virtual void ToggleFullscreen() override;

		virtual bool HasFocus() const override { return hasFocus; }

		virtual bool IsCursorEnabled() const override { return isCursorEnabled; }
		virtual void SetCursorEnabled(bool cursor) override;
		virtual void ToggleCursorEnabled() override;

		virtual bool ShouldClose() const override { return shouldClose; }

		virtual ContextAddressFunc GetContextAddressFunc() const override;

	private:
		GLFWwindow* window;

		WindowData windowData;

		bool isFullscreen;
		bool hasFocus;
		bool isCursorEnabled;
		bool shouldClose;

		static WindowData& GetWindowData(GLFWwindow* window);

		void InitWindow();
		void InitCallbacks();
	};
}

