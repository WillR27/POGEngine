#include "POGCorePCH.h"
#include "Window.h"

#include "POGLog.h"

#include "WindowsWindow.h"

namespace POG::Core
{
    std::unique_ptr<Window> Window::Create(std::string name)
    {
        return std::make_unique<WindowsWindow>(name);
    }

    Window::Window(std::string name)
        : name(name)
    {
        POG_INFO("Creating window \"{0}\"!", name);
    }
}