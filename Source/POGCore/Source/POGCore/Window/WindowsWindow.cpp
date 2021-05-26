#include "POGCorePCH.h"
#include "WindowsWindow.h"

#include "POGCore/Application/Application.h"
#include "POGCore/Event/Events.h"

#include "POGDebug.h"
#include "POGLog.h"
#include "POGRender.h"

#include <GLFW/glfw3.h>

namespace POG::Core
{
	static void GLFWErrorCallback(int error, const char* description)
	{
		POG_ERROR("GLFW error {0}: {1}", error, description);
	}

	WindowData& WindowsWindow::GetWindowData(GLFWwindow* window)
	{
		return *(WindowData*)glfwGetWindowUserPointer(window);
	}

	WindowsWindow::WindowsWindow(std::string name)
		: Window::Window(name)
		, window(nullptr)
		, windowData()
		, isFullscreen(false)
		, hasFocus(true)
		, isCursorEnabled(true)
	{
	}

	WindowsWindow::~WindowsWindow()
	{
	}

	void WindowsWindow::Init()
	{
		InitWindow();
		InitCallbacks();
	}

	void WindowsWindow::Close()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void WindowsWindow::InitWindow()
	{
		POG_INFO("Initialising window \"{0}\"!", GetName());

		windowData.width = Application::GetInstance().GetWidth();
		windowData.height = Application::GetInstance().GetHeight();

		POG_INFO("Initialising GLFW!");
		int success = glfwInit();
		POG_ASSERT(success, "GLFW failed to initialise!");

		glfwSetErrorCallback(GLFWErrorCallback);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

#ifdef POG_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

		POG_INFO("Creating window with OpenGL context!");
		window = glfwCreateWindow(windowData.width, windowData.height, GetName().c_str(), NULL, NULL);
		POG_ASSERT(window, "Window or OpenGL context failed!");

		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &windowData);
	}

	void WindowsWindow::InitCallbacks()
	{
		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
			{
				WindowData& windowData = GetWindowData(window);

				Application::GetInstance().GetMainEventBus().Publish(WindowCloseEvent());
			});

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
			{
				if (width != 0 && height != 0)
				{
					WindowData& windowData = GetWindowData(window);
					windowData.width = width;
					windowData.height = height;

					Application::GetInstance().GetMainEventBus().Publish(WindowSizeEvent(width, height));
				}
			});

		glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int hasFocus)
			{
				WindowData& windowData = GetWindowData(window);
				windowData.hasFocus = hasFocus;

				Application::GetInstance().GetMainEventBus().Publish(WindowFocusEvent(hasFocus));
			});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& windowData = GetWindowData(window);

				Application::GetInstance().GetMainEventBus().Publish(KeyEvent(key, scancode, action, mods));
			});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double posX, double posY)
			{
				WindowData& windowData = GetWindowData(window);

				Application::GetInstance().GetMainEventBus().Publish(MouseMoveEvent(static_cast<float>(posX), static_cast<float>(posY)));
			});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& windowData = GetWindowData(window);

				Application::GetInstance().GetMainEventBus().Publish(MouseButtonEvent(button, action, mods));
			});
	}

	void WindowsWindow::Input()
	{
		glfwPollEvents();
	}

	void WindowsWindow::Frame()
	{

	}

	void WindowsWindow::SwapBuffers()
	{
		glfwSwapBuffers(window);
	}

	void WindowsWindow::HandleWindowFocusEvent(WindowFocusEvent& e)
	{
		POG_INFO(e.ToString());

		static bool wasFullscreen = false;

		if (e.hasFocus)
		{
			if (wasFullscreen)
			{
				SetFullscreen(true);
			}
		}
		else
		{
			if (IsFullscreen())
			{
				wasFullscreen = true;
				SetFullscreen(false);
			}
		}

		hasFocus = e.hasFocus;

		e.SetHandled();
	}

	void WindowsWindow::UpdateView(View view)
	{
		glfwSetWindowSize(window, view.GetWidth(), view.GetHeight());

		Render::SetViewport(0, 0, view.GetWidth(), view.GetHeight());
	}

	void WindowsWindow::SetFullscreen(bool isFullscreen)
	{
		static int width, height, x, y;
		this->isFullscreen = isFullscreen;

		if (isFullscreen)
		{
			width = windowData.width;
			height = windowData.height;
			glfwGetWindowPos(window, &x, &y);

			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
			Application::GetInstance().GetMainEventBus().Publish(WindowSizeEvent(mode->width, mode->height));
		}
		else
		{
			glfwSetWindowMonitor(window, nullptr, x, y, width, height, GLFW_DONT_CARE);
			Application::GetInstance().GetMainEventBus().Publish(WindowSizeEvent(width, height));
		}
	}

	void WindowsWindow::SetCursorEnabled(bool isCursorEnabled)
	{
		this->isCursorEnabled = isCursorEnabled;

		if (isCursorEnabled)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}

	ContextAddressFunc WindowsWindow::GetContextAddressFunc() const
	{
		return (ContextAddressFunc)glfwGetProcAddress;
	}

	void* WindowsWindow::GetActualWindow()
	{
		return window;
	}
}