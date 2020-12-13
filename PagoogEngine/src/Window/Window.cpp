#include "pgepch.h"
#include "Window.h"

#include "WindowsWindow.h"

namespace PEngine
{
	Window* Window::Create()
	{
		return new WindowsWindow();
	}
}