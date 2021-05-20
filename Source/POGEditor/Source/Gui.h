#pragma once

#include "POGRender.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace POG::Editor
{
	class Gui
	{
	public:
		Gui() = default;

		~Gui() = default;

		void Init();

		void Cleanup();

		void Frame();
		void StartStyle();
		void Dockspace();
		void GameWindow(Render::Texture& clientTexture);
		void EndStyle();
		void Render();

	private:
		ImVec4 clearColour;
	};
}

