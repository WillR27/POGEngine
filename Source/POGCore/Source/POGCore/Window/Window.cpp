#include "POGCorePCH.h"
#include "Window.h"

#include "POGLog.h"

#include "WindowsWindow.h"

namespace POG::Core
{
    Window* Window::Create(std::string name)
    {
        return new WindowsWindow(name);
    }

    Window::Window(std::string name)
        : name(name)
    {
        POG_INFO("Creating window \"{0}\"!", name);
    }
}