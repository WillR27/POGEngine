#include "POGEditorPCH.h"
#include "Gui.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <imgui_internal.h>

#include "POGCore.h"
#include "POGLog.h"

#include "POGEditor/POGEditor.h"
#include "POGEditor/POGEditorEvents.h"

#include "Icons.h"
#include "Styles.h"

namespace POG::Editor
{
	const ImGuiTreeNodeFlags Gui::BaseTreeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_SpanFullWidth;

	Gui::Gui()
		: context(nullptr)
		, io(nullptr)
		, dockspaceId(0)
		, dockspaceLoaded(false)
		, clientScene(nullptr)
		, selectedEntityId(Core::NullEntity)
		, clickedEntityId(Core::NullEntity)
		, selectedEntityChanged(false)
		, potentialEntitiesToDelete()
		, entitiesToDelete()
		, openEntityDeleteConfirmationDialog(false)
		, deleteEntitiesConfirmationDialog("The selected entity will be deleted along with all of \nits children.")
		, entityNameField("Name")
		, filesFolders(POGEditor::GetInstance().GetClientWorkspaceDirectory())
		, isClientWindowFocused(false)
		, shouldSetClientWindowFocused(false)
		, clearColour()
	{
	}

	void Gui::Init()
	{
		LoadIcons();

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		context = ImGui::CreateContext();
		io = &ImGui::GetIO();
		io->IniFilename = "editor.ini";
		io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

		ImGui::StyleColorsDark();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		style.DisplaySafeAreaPadding = ImVec2(0.0f, 0.0f);
		if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(Core::Application::GetInstance().GetWindow().GetActualWindow()), true);
		ImGui_ImplOpenGL3_Init("#version 410");

		clearColour = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		InitStyle();

		ImFontConfig fontConfig;
		fontConfig.OversampleH = 7;
		fontConfig.OversampleV = 5;
		fontConfig.RasterizerMultiply = 1.2f;
		io->FontDefault = io->Fonts->AddFontFromFileTTF("Resources\\Fonts\\Segoe UI.ttf", 16.0f, &fontConfig);

		deleteEntitiesConfirmationDialog.AddButton("Delete", [this] { entitiesToDelete = potentialEntitiesToDelete; SetSelectedEntity(Core::NullEntity); });
		deleteEntitiesConfirmationDialog.AddButton("Cancel", [this] { potentialEntitiesToDelete.clear(); });
	}

	void Gui::InitStyle()
	{
		ImGuiStyle& style = ImGui::GetStyle();

		style.WindowMenuButtonPosition = ImGuiDir_Right;

		style.WindowBorderSize = WindowBorderSize;
		style.WindowPadding = ImVec2(WindowPaddingX, WindowPaddingY);

		style.TabBorderSize = TabBorderSize;
		style.TabRounding = TabRounding;

		style.FrameBorderSize = FrameBorderSize;
		style.FramePadding = ImVec2(FramePaddingX, FramePaddingY);

		style.ScrollbarRounding = ScrollbarRounding;

		style.ChildBorderSize = ChildBorderThickness;
		style.ChildRounding = ChildRounding;

		style.IndentSpacing = IndentSpacing;

		style.ItemSpacing = ImVec2(ItemSpacingRight, ItemSpacingBottom);
		style.ItemInnerSpacing = ImVec2(ItemInnerSpacingRight, ItemInnerSpacingBottom);

		ImVec4* colours = style.Colors;

		colours[ImGuiCol_DockingPreview] = DefaultGrey;

		colours[ImGuiCol_WindowBg] = DarkerGrey;

		colours[ImGuiCol_MenuBarBg] = DarkerGrey;

		colours[ImGuiCol_TitleBg] = DarkererGrey;
		colours[ImGuiCol_TitleBgActive] = DarkererGrey;

		colours[ImGuiCol_Tab] = DarkererGrey;
		colours[ImGuiCol_TabHovered] = DarkerGrey;
		colours[ImGuiCol_TabActive] = DarkerGrey;
		colours[ImGuiCol_TabUnfocused] = DarkererGrey;
		colours[ImGuiCol_TabUnfocusedActive] = DarkerGrey;

		colours[ImGuiCol_Separator] = DarkererGrey;
		colours[ImGuiCol_SeparatorHovered] = DarkererGrey;
		colours[ImGuiCol_SeparatorActive] = DarkererGrey;

		colours[ImGuiCol_FrameBg] = DefaultGrey;
		colours[ImGuiCol_FrameBgHovered] = LighterGrey;
		colours[ImGuiCol_FrameBgActive] = LightererGrey;

		colours[ImGuiCol_ScrollbarBg] = Transparent;
		colours[ImGuiCol_ScrollbarGrab] = LighterGrey;
		colours[ImGuiCol_ScrollbarGrabHovered] = LightererGrey;
		colours[ImGuiCol_ScrollbarGrabActive] = LightestGrey;
		
		colours[ImGuiCol_ResizeGrip] = LighterGrey;
		colours[ImGuiCol_ResizeGripHovered] = LightererGrey;
		colours[ImGuiCol_ResizeGripActive] = LightestGrey;
		
		colours[ImGuiCol_Button] = DefaultGrey;
		colours[ImGuiCol_ButtonHovered] = LighterGrey;
		colours[ImGuiCol_ButtonActive] = LightestGrey;
		
		colours[ImGuiCol_SliderGrab] = DefaultGrey;
		colours[ImGuiCol_SliderGrabActive] = LighterGrey;
		
		colours[ImGuiCol_CheckMark] = DefaultGrey;
		
		colours[ImGuiCol_Header] = DefaultGrey;
		colours[ImGuiCol_HeaderHovered] = LighterGrey;
		colours[ImGuiCol_HeaderActive] = LightererGrey;
		
		colours[ImGuiCol_TextSelectedBg] = DefaultGrey;
	}

	void Gui::Cleanup()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		FreeIcons();
	}

	void Gui::Frame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		dockspaceLoaded = context->SettingsWindows.size();
		selectedEntityChanged = false;
	}

	void Gui::Dockspace()
	{
		dockspaceId = ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		if (!dockspaceLoaded)
		{
			ImVec2 dockspaceSize = ImGui::GetMainViewport()->Size;

			ImGui::DockBuilderRemoveNode(dockspaceId); // Clear out existing layout
			ImGui::DockBuilderAddNode(dockspaceId, ImGuiDockNodeFlags_DockSpace); // Add empty node
			ImGui::DockBuilderSetNodeSize(dockspaceId, dockspaceSize);

			ImGuiID dockMainId = dockspaceId; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
			ImGuiID dockLeftId = ImGui::DockBuilderSplitNode(dockMainId, ImGuiDir_Left, 0.20f, NULL, &dockMainId);
			ImGuiID dockRightId = ImGui::DockBuilderSplitNode(dockMainId, ImGuiDir_Right, 0.30f, NULL, &dockMainId);

			ImGui::DockBuilderDockWindow("Entities", dockLeftId);
			ImGui::DockBuilderDockWindow("Properties", dockRightId);
			ImGui::DockBuilderDockWindow("Game", dockMainId);
			ImGui::DockBuilderFinish(dockspaceId);

			dockspaceLoaded = true;
		}
	}

	void Gui::EntitiesPanel()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(ItemSpacingRight, 0.0f));
		ImGui::Begin("Entities", NULL, ImGuiWindowFlags_HorizontalScrollbar);
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 2.0f));
			if (clientScene)
			{
				clickedEntityId = Core::NullEntity;

				Core::ECSManager& clientECSManager = clientScene->GetECSManager();

				// Find entities without parents
				for (Core::EntityId entityId : clientECSManager.GetUsedEntityIds())
				{
					// If it has a parent continue
					if (clientECSManager.GetParent(entityId) != Core::NullEntity)
					{
						continue;
					}

					EntitiesPanelAddNode(entityId);
				}
			}
			ImGui::PopStyleVar();
		}
		ImGui::End();
		ImGui::PopStyleVar(2);

		if (clickedEntityId != Core::NullEntity)
		{
			SetSelectedEntity(clickedEntityId);
		}
	}

	void Gui::EntitiesPanelAddNode(Core::EntityId entityId)
	{
		Core::ECSManager& clientECSManager = clientScene->GetECSManager();
		std::string entityName = clientECSManager.GetName(entityId);

		ImGuiTreeNodeFlags flags = BaseTreeFlags;
		if (selectedEntityId == entityId)
		{
			flags |= ImGuiTreeNodeFlags_Selected;
		}

		if (!clientECSManager.HasChildren(entityId))
		{
			flags |= ImGuiTreeNodeFlags_Leaf;
		}

		bool isOpen = ImGui::TreeNodeEx((void*)(intptr_t)entityId, flags, entityName.c_str());

		if (ImGui::IsItemClicked(ImGuiMouseButton_Left) || ImGui::IsItemClicked(ImGuiMouseButton_Right))
		{
			clickedEntityId = entityId;
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(FramePaddingX, FramePaddingY));
		if (ImGui::BeginPopupContextItem())
		{
			clickedEntityId = entityId;

			if (ImGui::MenuItem("Delete"))
			{
				deleteEntitiesConfirmationDialog.Open();

				potentialEntitiesToDelete.push_back(entityId);
			}

			ImGui::EndPopup();
		}
		ImGui::PopStyleVar();

		if (isOpen)
		{
			for (Core::EntityId childId : clientECSManager.GetChildren(entityId))
			{ 
				EntitiesPanelAddNode(childId);
			}

			ImGui::TreePop();
		}
	}

	void Gui::PropertiesPanel()
	{
		Core::ECSManager& clientECSManager = clientScene->GetECSManager();

		ImGui::Begin("Properties");
		{
			if (selectedEntityId != Core::NullEntity)
			{
				std::string entityName = clientECSManager.GetName(selectedEntityId);

				if (selectedEntityChanged)
				{
					entityNameField.SetText(_strdup(entityName.c_str()));
				}

				entityNameField.Render();

				if (entityNameField.HasFinishedEditing())
				{
					clientECSManager.SetName(selectedEntityId, entityNameField.GetText());
				}

				if (clientECSManager.HasComponent<Core::AttachedCamera>(selectedEntityId))
				{
					AttachedCamera camera(clientECSManager.GetComponent<Core::AttachedCamera>(selectedEntityId));
					camera.Render();
				}

				if (clientECSManager.HasComponent<Core::Transform>(selectedEntityId))
				{
					Transform transform(clientECSManager.GetComponent<Core::Transform>(selectedEntityId));
					transform.Render();

					if (transform.HasChanged())
					{
						clientECSManager.SetComponent(selectedEntityId, transform.GetTransform());
					}
				}
			}
		}
		ImGui::End();
	}

	void Gui::AssetsPanel()
	{
		ImGui::Begin("Assets");
		{
			filesFolders.Render();
		}
		ImGui::End();
	}

	void Gui::MainMenu()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit", nullptr))
				{
					Core::Application::GetInstance().Exit();
				}

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
				if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item

				ImGui::Separator();

				if (ImGui::MenuItem("Cut", "CTRL+X")) {}
				if (ImGui::MenuItem("Copy", "CTRL+C")) {}
				if (ImGui::MenuItem("Paste", "CTRL+V")) {}

				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}

	void Gui::ShowModalDialogs()
	{
		deleteEntitiesConfirmationDialog.Render();
	}

	void Gui::GameWindow(Render::Texture& clientTexture)
	{
		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		bool showDemoWindow = true;
		if (showDemoWindow)
		{
			ImGui::ShowDemoWindow(&showDemoWindow);
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Game", NULL, ImGuiWindowFlags_HorizontalScrollbar);
		{
			ImVec2 buttonSize(60.0f, 22.0f);

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
			ImGui::Indent(ImGui::GetWindowSize().x / 2.0f - 90.0f);
			if (ImGui::Button("Play", buttonSize))
			{
				Core::Application::GetInstance().GetMainEventBus().Publish(ClientPlayEvent());
			}
			ImGui::Indent(-(ImGui::GetWindowSize().x / 2.0f - 90.0f));

			ImGui::SameLine();
			if (ImGui::Button("Pause", buttonSize))
			{
				Core::Application::GetInstance().GetMainEventBus().Publish(ClientPauseEvent());
			}

			ImGui::SameLine();
			if (ImGui::Button("Stop", buttonSize))
			{
				Core::Application::GetInstance().GetMainEventBus().Publish(ClientStopEvent());
			}
			ImGui::PopStyleVar();

			if (shouldSetClientWindowFocused)
			{
				ImGui::SetNextWindowFocus();
				shouldSetClientWindowFocused = false;
			}

			ImGui::BeginChild("Game Render");
			{
				if (!shouldSetClientWindowFocused)
				{
					bool wasClientWindowFocused = isClientWindowFocused;
					isClientWindowFocused = ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows);
					if (wasClientWindowFocused != isClientWindowFocused)
					{
						Core::Application::GetInstance().GetMainEventBus().Publish(ClientFocusedEvent(isClientWindowFocused));
					}
				}

				ImVec2 wsize = ImGui::GetWindowSize();
				ImGui::Image((ImTextureID)((unsigned long long)clientTexture), wsize, ImVec2(0, 1), ImVec2(1, 0));
			}
			ImGui::EndChild();
		}
		ImGui::End();
		ImGui::PopStyleVar();
	}

	void Gui::ApplyChanges()
	{
		Core::ECSManager& clientECSManager = clientScene->GetECSManager();

		for (Core::EntityId entityId : entitiesToDelete)
		{
			clientECSManager.DestroyEntity(entityId);
		}

		entitiesToDelete.clear();
	}

	void Gui::Render()
	{
		// TODO: Replace with something proper if possible?
		// Hack to prevent game window losing focus when clicking without cursor
		if (!POGEditor::GetInstance().IsCursorEnabled())
		{
			// Set left mouse button to false before ImGui::Render()
			// As this is where the window changes focus if clicked
			io->MouseClicked[0] = false;
		}

		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize((GLFWwindow*)Core::Application::GetInstance().GetWindow().GetActualWindow(), &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clearColour.x * clearColour.w, clearColour.y * clearColour.w, clearColour.z * clearColour.w, clearColour.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();
		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void Gui::SetClientWindowFocused(bool isClientWindowFocused)
	{
		shouldSetClientWindowFocused = isClientWindowFocused;
	}

	void Gui::SetCursorEnabled(bool isCursorEnabled)
	{
		if (isCursorEnabled)
		{
			io->ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
		}
		else
		{
			io->ConfigFlags |= ImGuiConfigFlags_NoMouse;
		}
	}

	void Gui::SetSelectedEntity(Core::EntityId selectedEntityId)
	{
		if (this->selectedEntityId != selectedEntityId)
		{
			selectedEntityChanged = true;
			this->selectedEntityId = selectedEntityId;
		}
	}
}