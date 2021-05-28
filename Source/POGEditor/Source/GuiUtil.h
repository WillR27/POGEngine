#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace POG::Editor
{
	bool ConfirmationDialog(const char* title, const char* message);
}

