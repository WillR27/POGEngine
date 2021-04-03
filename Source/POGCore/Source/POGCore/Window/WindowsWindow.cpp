#include "POGCorePCH.h"
#include "WindowsWindow.h"

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
		, shouldClose(false)
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

	void WindowsWindow::InitWindow()
	{
		POG_INFO("Initialising window \"{0}\"!", GetName());

		windowData.width = 1000;
		windowData.height = 800;
		windowData.eventCallback = [](Event& e)
		{
			POG_WARN("Window event callback has not been set!");
		};

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
		window = glfwCreateWindow(1000, 800, GetName().c_str(), NULL, NULL);
		POG_ASSERT(window, "Window or OpenGL context failed!");

		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &windowData);
	}

	void WindowsWindow::InitCallbacks()
	{
		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
			{
				WindowData& windowData = GetWindowData(window);

				WindowCloseEvent e;
				windowData.eventCallback(e);
			});

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
			{
				if (width != 0 && height != 0)
				{
					WindowData& windowData = GetWindowData(window);
					windowData.width = width;
					windowData.height = height;

					WindowSizeEvent e(width, height);
					windowData.eventCallback(e);
				}
			});

		glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int hasFocus)
			{
				WindowData& windowData = GetWindowData(window);
				windowData.hasFocus = hasFocus;

				WindowFocusEvent e(hasFocus);
				windowData.eventCallback(e);
			});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& windowData = GetWindowData(window);

				KeyEvent e(key, scancode, action, mods);
				windowData.eventCallback(e);
			});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double posX, double posY)
			{
				WindowData& windowData = GetWindowData(window);

				MouseMoveEvent e(static_cast<float>(posX), static_cast<float>(posY));
				windowData.eventCallback(e);
			});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& windowData = GetWindowData(window);

				MouseButtonEvent e(button, action, mods);
				windowData.eventCallback(e);
			});
	}

	void WindowsWindow::InputUpdate()
	{
		glfwPollEvents();
	}

	void WindowsWindow::FrameUpdate()
	{
		Render::Render::ClearColour(0.3f, 0.7f, 0.9f, 1.0f);
		Render::Render::ClearColourBuffer();
		Render::Render::ClearDepthBuffer();
	}

	void WindowsWindow::SwapBuffers()
	{
		glfwSwapBuffers(window);
	}

	bool WindowsWindow::HandleWindowCloseEvent(WindowCloseEvent& e)
	{
		//POG_INFO(e);

		shouldClose = true;

		return true;
	}

	bool WindowsWindow::HandleWindowSizeEvent(WindowSizeEvent& e)
	{
		//POG_INFO(e);

		glfwSetWindowSize(window, e.width, e.height);

		Render::Render::SetViewport(0, 0, e.width, e.height);

		return true;
	}

	bool WindowsWindow::HandleWindowFocusEvent(WindowFocusEvent& e)
	{
		//POG_INFO(e);

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

		return true;
	}

	void WindowsWindow::SetEventCallback(EventCallback eventCallback)
	{
	}

	void WindowsWindow::SetFullscreen(bool isFullscreen)
	{
		this->isFullscreen = isFullscreen;
	}

	void WindowsWindow::ToggleFullscreen()
	{
		SetFullscreen(!IsFullscreen());
	}

	void WindowsWindow::SetCursorEnabled(bool isCursorEnabled)
	{
		this->isCursorEnabled = isCursorEnabled;
	}

	void WindowsWindow::ToggleCursorEnabled()
	{
		SetCursorEnabled(!IsCursorEnabled());
	}

	ContextAddressFunc WindowsWindow::GetContextAddressFunc() const
	{
		return (ContextAddressFunc)glfwGetProcAddress;
	}
}