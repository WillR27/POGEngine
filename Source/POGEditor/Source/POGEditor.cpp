#include "POGEditorPCH.h"

#include "POGCore.h"
#include "POGRender.h"

#include "POGCore/Main.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace POG::Editor
{
	class POGEditorScene : public POG::Core::Scene
	{
	public:
		POGEditorScene() = default;

		virtual ~POGEditorScene() = default;

		void Init() override
		{

		}

		void Exit() override
		{
			// Cleanup
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}

		void Update(float dt) override
		{

		}

		void FrameUpdate(float alpha) override
		{
			bool show_demo_window = true;
			bool show_another_window = false;
			ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
			if (show_demo_window)
				ImGui::ShowDemoWindow(&show_demo_window);

			// Rendering
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		void HandleEvent(Core::Event& e) override
		{

		}
	};

	class POGEditorApplication : public POG::Core::Application
	{
	public:
		POGEditorApplication()
			: Application::Application("POG Example")
		{
		}

		void Init() override
		{
			POG::Render::Render::SetContextAddressFunc(GetWindow().GetContextAddressFunc());

			inputManager.AddAction("Quit", Core::InputInfo(Core::InputType::Keyboard, PG_KEY_ESCAPE, PG_KEY_RELEASE, PG_MOD_ANY));
			inputManager.AddAction("Fullscreen", Core::InputInfo(Core::InputType::Keyboard, PG_KEY_F11, PG_KEY_RELEASE, PG_MOD_ANY));

			activeScene = std::make_unique<POGEditorScene>();

			// Setup Dear ImGui context
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

			// Setup Dear ImGui style
			ImGui::StyleColorsDark();
			//ImGui::StyleColorsClassic();

			// Setup Platform/Renderer backends
			ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(GetWindow().GetActualWindow()), true);
			ImGui_ImplOpenGL3_Init("#version 150");
		}

		void Input(Core::InputPackage& inputPackage, float dt) override
		{
			if (inputPackage.HasActionOccurred("Quit", true))
			{
				Quit();
			}

			if (inputPackage.HasActionOccurred("Fullscreen", true))
			{
				GetWindow().ToggleFullscreen();
			}
		}
	};
}

std::unique_ptr<POG::Core::Application> POG::Core::CreateApplication()
{
	return std::make_unique<POG::Editor::POGEditorApplication>();
}