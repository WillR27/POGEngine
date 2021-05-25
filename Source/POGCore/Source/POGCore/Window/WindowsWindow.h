#pragma once

#include "POGCommon.h"

#include "Window.h"

// If we include GLFW inside this header then we get APIENTRY redefinitions
struct GLFWwindow;

namespace POG::Core
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(std::string name);

		virtual ~WindowsWindow();

		virtual void Init() override;
		virtual void Close() override;

		virtual void Input() override;
		virtual void Frame() override;

		virtual void SwapBuffers() override;

		virtual bool HandleWindowFocusEvent(WindowFocusEvent& e) override;
		
		virtual void UpdateView(View view) override;

		virtual void SetEventCallback(EventCallback eventCallback) override;

		virtual bool IsFullscreen() const override { return isFullscreen; }
		virtual void SetFullscreen(bool isFullscreen) override;

		virtual bool HasFocus() const override { return hasFocus; }

		virtual bool IsCursorEnabled() const override { return isCursorEnabled; }
		virtual void SetCursorEnabled(bool isCursorEnabled) override;

		virtual ContextAddressFunc GetContextAddressFunc() const override;

		virtual void* GetActualWindow() override;

	private:
		GLFWwindow* window;

		WindowData windowData;

		bool isFullscreen;
		bool hasFocus;
		bool isCursorEnabled;

		static WindowData& GetWindowData(GLFWwindow* window);

		void InitWindow();
		void InitCallbacks();
	};
}

