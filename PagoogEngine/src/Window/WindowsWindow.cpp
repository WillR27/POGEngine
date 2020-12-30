#include "pgepch.h"
#include "WindowsWindow.h"

#include "Event/WindowEvents.h"
#include "Event/InputEvents.h"
#include "Game/Camera.h"
#include "Render/Core/Shader.h"
#include "Render/Core/Render.h"

#include <glad/glad.h>

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
	{
	}

	WindowsWindow::~WindowsWindow()
	{
		Close();
	}

	void WindowsWindow::InputUpdate()
	{
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
				WindowData& windowData = GetWindowData(window);
				windowData.width = width;
				windowData.height = height;

				WindowSizeEvent e(width, height);
				windowData.eventCallback(e);
			});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& windowData = GetWindowData(window);

				KeyEvent e(key, scancode, action, mods);
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

	void WindowsWindow::Close()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	bool WindowsWindow::HandleWindowCloseEvent(WindowCloseEvent& e)
	{
		shouldClose = true;

		return true;
	}

	bool WindowsWindow::HandleWindowSizeEvent(WindowSizeEvent& e)
	{
		glfwSetWindowSize(window, e.width, e.height);
		glViewport(0, 0, e.width, e.height);
		Camera::MainCamera->SetAspectRatio(static_cast<float>(e.width) / e.height);

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