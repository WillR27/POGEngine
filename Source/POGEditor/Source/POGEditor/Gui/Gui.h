#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "POGCore.h"
#include "POGRender.h"

#include "Components.h"
#include "Dialogs.h"
#include "FilesFolders.h"
#include "Text.h"

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
		void Dockspace();
		void EntitiesPanel();
		void PropertiesPanel();
		void AssetsPanel();
		void MainMenu();
		void ShowModalDialogs();
		void GameWindow(Render::Texture& clientTexture);
		void ApplyChanges();
		void Render();

		void SetScene(Core::Scene* clientScene) { this->clientScene = clientScene; }

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
		bool selectedEntityChanged;
		std::vector<Core::EntityId> potentialEntitiesToDelete;
		std::vector<Core::EntityId> entitiesToDelete;
		bool openEntityDeleteConfirmationDialog;

		ConfirmationDialog deleteEntitiesConfirmationDialog;

		TextField entityNameField;

		FilesFolders filesFolders;

		bool isClientWindowFocused;
		bool shouldSetClientWindowFocused;

		ImVec4 clearColour;

		void InitStyle();

		void EntitiesPanelAddNode(Core::EntityId entityId);

		void SetSelectedEntity(Core::EntityId selectedEntityId);
	};
}

