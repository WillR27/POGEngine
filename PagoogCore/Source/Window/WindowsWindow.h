#pragma once

#include <GLFW/include/GLFW/glfw3.h>

#include "Window.h"

namespace Pagoog::Core
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(std::string name);

		virtual ~WindowsWindow();

		virtual void Init() override;

		virtual bool ShouldClose() override;

	private:
		GLFWwindow* window;
	};
}

