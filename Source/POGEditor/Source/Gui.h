#pragma once

#include "POGCore.h"
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

		void SetScene(Core::Scene* clientScene) { this->clientScene = clientScene; }
		void Frame();
		void StartStyle();
		void Dockspace();
		void EntityExplorer();
		void GameWindow(Render::Texture& clientTexture);
		void ShowModalDialogs();
		void MainMenu();
		void ApplyChanges();
		void EndStyle();
		void Render();

		void SetClientWindowFocused(bool isClientWindowFocused);
		void SetCursorEnabled(bool isCursorEnabled);

		//bool IsClientFocused() const { return isClientFocused; }
		//bool ShouldLoadClient() const { return shouldLoadClient; }
		//bool IsClientPaused() const { return isClientPaused; }

	private:
		static const ImGuiTreeNodeFlags BaseTreeFlags;

		ImGuiContext* context;
		ImGuiIO* io;

		ImGuiID dockspaceId;

		bool dockspaceLoaded;

		Core::Scene* clientScene;
		Core::EntityId selectedEntityId;
		Core::EntityId clickedEntityId;
		std::vector<Core::EntityId> potentialEntitiesToDelete;
		std::vector<Core::EntityId> entitiesToDelete;
		bool openEntityDeleteConfirmationDialog;

		bool isClientWindowFocused;
		bool shouldSetClientWindowFocused;

		ImVec4 clearColour;

		void EntityExplorerAddNode(Core::EntityId entityId);
	};
}

