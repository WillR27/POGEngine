#include "POGEditorPCH.h"
#include "Gui.h"

#include "POGEditor.h"

#include "POGCore.h"
#include "POGLog.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <imgui_internal.h>

namespace POG::Editor
{
	Gui::Gui()
		: context(nullptr)
		, io(nullptr)
		, dockspaceId(0)
		, dockspaceLoaded(false)
		, isClientFocused(true)
		, shouldLoadClient(false)
		, isClientPaused(false)
	{
	}

	void Gui::Init()
	{
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
	}

	void Gui::Cleanup()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void Gui::Frame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		dockspaceLoaded = context->SettingsWindows.size();
	}

	void Gui::StartStyle()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));

		ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);

		ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0, 0));
		ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
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

	void Gui::Dockspace()
	{
		bool active = true;

		const ImGuiViewport* mainViewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(ImVec2(mainViewport->WorkPos.x, mainViewport->WorkPos.y));
		ImGui::SetNextWindowSize(ImVec2(mainViewport->WorkSize.x, mainViewport->WorkSize.y));
		ImGui::Begin("Dock Space Window", &active, ImGuiWindowFlags_None | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs);
		{
			dockspaceId = ImGui::GetID("Dock Space");
			ImVec2 dockspaceSize = mainViewport->Size;
			ImGui::DockSpace(dockspaceId, dockspaceSize, ImGuiDockNodeFlags_None);
			
			if (!dockspaceLoaded)
			{
				ImGui::DockBuilderRemoveNode(dockspaceId); // Clear out existing layout
				ImGui::DockBuilderAddNode(dockspaceId, ImGuiDockNodeFlags_DockSpace); // Add empty node
				ImGui::DockBuilderSetNodeSize(dockspaceId, dockspaceSize);

				ImGuiID dockMainId = dockspaceId; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
				ImGuiID dockLeftId= ImGui::DockBuilderSplitNode(dockMainId, ImGuiDir_Left, 0.30f, NULL, &dockMainId);

				ImGui::DockBuilderDockWindow("Dear ImGui Demo", dockLeftId);
				ImGui::DockBuilderDockWindow("Game Window", dockMainId);
				ImGui::DockBuilderFinish(dockspaceId);

				dockspaceLoaded = true;
			}
		}
		ImGui::End();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		bool showDemoWindow = true;
		if (showDemoWindow)
		{
			ImGui::ShowDemoWindow(&showDemoWindow);
		}
	}

	void Gui::GameWindow(Render::Texture& clientTexture)
	{
		ImGui::Begin("Game Window");
		{
			isClientFocused = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows);
			
			if (ImGui::Button("Play"))
			{
				shouldLoadClient = true;
				isClientPaused = false;
			}

			ImGui::SameLine();
			if (ImGui::Button("Pause"))
			{
				isClientPaused = true;
			}

			ImGui::SameLine();
			if (ImGui::Button("Stop"))
			{
				shouldLoadClient = false;
				isClientPaused = true;
			}

			ImGui::BeginChild("Game Render");
			ImVec2 wsize = ImGui::GetWindowSize();
			ImGui::Image((ImTextureID)((unsigned int)clientTexture), wsize, ImVec2(0, 1), ImVec2(1, 0));
			ImGui::EndChild();
		}
		ImGui::End();
	}

	void Gui::EndStyle()
	{
		ImGui::PopStyleVar(9);
	}

	void Gui::Render()
	{
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
}