#include "PagoogCorePCH.h"
#include "WindowsWindow.h"

namespace Pagoog::Core
{
	WindowsWindow::WindowsWindow(std::string name)
		: Window::Window(name)
		, window(nullptr)
	{
	}

	WindowsWindow::~WindowsWindow()
	{
	}

	void WindowsWindow::Init()
	{
		PG_INFO("Initialising window \"{0}\"!", GetName());

		int success = glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

#ifdef PG_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

		window = glfwCreateWindow(1000, 800, GetName().c_str(), NULL, NULL);

		glfwMakeContextCurrent(window);
	}

	bool WindowsWindow::ShouldClose()
	{
		return false;
	}

	ContextAddressFunc WindowsWindow::GetContextAddressFunc() const
	{
		return (ContextAddressFunc)glfwGetProcAddress;
	}
}