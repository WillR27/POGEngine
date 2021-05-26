#pragma once

#include "Window.h"

#include "POGCommon.h"

// If we include GLFW inside this header then we get APIENTRY redefinitions
struct GLFWwindow;

namespace POG::Core
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(std::string name);

		virtual ~WindowsWindow();

		void Init() override;
		void Close() override;

		void Input() override;
		void Frame() override;

		void SwapBuffers() override;

		void HandleWindowFocusEvent(WindowFocusEvent& e) override;
		
		void UpdateView(View view) override;

		bool IsFullscreen() const override { return isFullscreen; }
		void SetFullscreen(bool isFullscreen) override;

		bool HasFocus() const override { return hasFocus; }

		bool IsCursorEnabled() const override { return isCursorEnabled; }
		void SetCursorEnabled(bool isCursorEnabled) override;

		ContextAddressFunc GetContextAddressFunc() const override;

		void* GetActualWindow() override;

	private:
		static WindowData& GetWindowData(GLFWwindow* window);

		GLFWwindow* window;

		WindowData windowData;

		bool isFullscreen;
		bool hasFocus;
		bool isCursorEnabled;

		void InitWindow();
		void InitCallbacks();
	};
}

