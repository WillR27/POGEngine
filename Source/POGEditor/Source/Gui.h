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
		Gui();

		~Gui() = default;

		void Init();

		void Cleanup();

		void Frame();
		void StartStyle();
		void MainMenu();
		void Dockspace();
		void GameWindow(Render::Texture& clientTexture);
		void EndStyle();
		void Render();

		void SetClientWindowFocused(bool isClientWindowFocused);

		void SetCursorEnabled(bool isCursorEnabled);

		//bool IsClientFocused() const { return isClientFocused; }
		//bool ShouldLoadClient() const { return shouldLoadClient; }
		//bool IsClientPaused() const { return isClientPaused; }

	private:
		ImGuiContext* context;
		ImGuiIO* io;

		ImGuiID dockspaceId;

		bool dockspaceLoaded;

		ImVec4 clearColour;

		bool isClientWindowFocused;
		bool shouldSetClientWindowFocused;
	};
}

