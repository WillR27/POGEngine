#include "pgepch.h"
#include "WindowsWindow.h"

#include <glad/glad.h>

#include "Event/WindowEvents.h"
#include "Event/InputEvents.h"
#include "Render/Core/Shader.h"
#include "Render/Core/Render.h"
#include "Scene/Camera.h"

namespace PEngine
{
	static void GLFWErrorCallback(int error, const char* description)
	{
		PG_ERROR("GLFW error {0}: {1}", error, description);
	}

	WindowsWindow::WindowsWindow()
		: window(nullptr)
		, shouldClose(false)
		, fullscreen(false)
		, hasFocus(true)
		, cursor(true)
	{
	}

	WindowsWindow::~WindowsWindow()
	{
		Close();
	}

	void WindowsWindow::InputUpdate()
	{
		Input::ResetMouseDeltas();
		glfwPollEvents();
	}

	void WindowsWindow::Init()
	{
		InitWindow();
		InitCallbacks();
	}

	void WindowsWindow::InitWindow()
	{
		windowData.width = 1000;
		windowData.height = 800;
		windowData.eventCallback = [](Event& e)
		{
			PG_WARN("Event callback has not been set!");
		};

		PG_INFO("Initialising GLFW!");
		int success = glfwInit();
		PG_ASSERT(success, "GLFW failed to initialise!");

		// Set error callback for any internal GLFW errors
		glfwSetErrorCallback(GLFWErrorCallback);

		// Set minimum OpenGL version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		
#ifdef PG_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

		PG_INFO("Creating window with OpenGL context!");
		window = glfwCreateWindow(1000, 800, "Pagoog", NULL, NULL);
		PG_ASSERT(window, "Window or OpenGL context failed!");

		// Make sure our OpenGL context is set to our new window
		glfwMakeContextCurrent(window);

		glfwSetWindowUserPointer(window, &windowData);

		PG_INFO("Initialising Glad!");
		success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PG_ASSERT(success, "Glad failed to initialise!");
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

	void WindowsWindow::FrameUpdate()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void WindowsWindow::SwapBuffers()
	{
		glfwSwapBuffers(window);
	}

	bool WindowsWindow::IsFullscreen() const
	{
		return fullscreen;
	}

	void WindowsWindow::SetFullscreen(bool fullscreen)
	{
		static int width, height, x, y;
		this->fullscreen = fullscreen;

		Input::ResetMouseMovement();

		if (fullscreen)
		{
			width = windowData.width;
			height = windowData.height;
			glfwGetWindowPos(window, &x, &y);

			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
			HandleWindowSizeEvent(WindowSizeEvent(mode->width, mode->height));
		}
		else
		{
			glfwSetWindowMonitor(window, nullptr, x, y, width, height, GLFW_DONT_CARE);
			HandleWindowSizeEvent(WindowSizeEvent(width, height));
		}
	}

	void WindowsWindow::ToggleFullscreen()
	{
		SetFullscreen(!fullscreen);
	}

	bool WindowsWindow::HasFocus() const
	{
		return hasFocus;
	}

	bool WindowsWindow::HasCursor() const
	{
		return cursor;
	}

	void WindowsWindow::SetCursorMode(bool cursor)
	{
		this->cursor = cursor;
		glfwSetInputMode(window, GLFW_CURSOR, cursor ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
	}

	void WindowsWindow::ToggleCursorMode()
	{
		SetCursorMode(!cursor);
	}

	void WindowsWindow::Close()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	bool WindowsWindow::HandleWindowCloseEvent(WindowCloseEvent& e)
	{
		PG_INFO(e);

		shouldClose = true;

		return true;
	}

	bool WindowsWindow::HandleWindowSizeEvent(WindowSizeEvent& e)
	{
		PG_INFO(e);

		glfwSetWindowSize(window, e.width, e.height);
		glViewport(0, 0, e.width, e.height);

		Camera::MainCamera->SetAspectRatio(static_cast<float>(e.width) / e.height);
		Input::ResetMouseMovement();

		return true;
	}

	bool WindowsWindow::HandleWindowFocusEvent(WindowFocusEvent& e)
	{
		PG_INFO(e);

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
		windowData.eventCallback = eventCallback;
	}

	bool WindowsWindow::ShouldClose() const
	{
		return shouldClose;
	}

	WindowsWindow::WindowData& WindowsWindow::GetWindowData(GLFWwindow* window)
	{
		return *(WindowData*)glfwGetWindowUserPointer(window);
	}
}