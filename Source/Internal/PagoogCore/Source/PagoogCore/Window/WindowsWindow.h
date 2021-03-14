#pragma once

#include <GLFW/glfw3.h>

#include "PagoogCommon.h"

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

		virtual ContextAddressFunc GetContextAddressFunc() const override;

	private:
		GLFWwindow* window;
	};
}

