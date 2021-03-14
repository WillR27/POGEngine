#include "PagoogCorePCH.h"
#include "Window.h"

#include "PagoogLog.h"

#include "WindowsWindow.h"

namespace Pagoog::Core
{
    std::unique_ptr<Window> Window::Create(std::string name)
    {
        return std::make_unique<WindowsWindow>(name);
    }

    Window::Window(std::string name)
        : name(name)
    {
        PG_INFO("Creating window \"{0}\"!", name);
    }
}