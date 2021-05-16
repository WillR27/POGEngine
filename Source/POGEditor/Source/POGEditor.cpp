#include "POGEditorPCH.h"

#include "POGCore.h"
#include "POGRender.h"

#include "POGCore/Main.h"

#include "glad/glad.h"

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
			Render::Render::Init();

			glGenFramebuffers(1, &fbo);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);

			glGenTextures(1, &tex);
			glBindTexture(GL_TEXTURE_2D, tex);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
		}

		void Exit() override
		{
			glDeleteFramebuffers(1, &fbo);

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
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			Render::Render::ClearColour(0.8f, 0.1f, 0.4f, 1.0f);
			Render::Render::ClearColourBuffer();
			Render::Render::ClearDepthBuffer();

			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			
			ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
			if (show_demo_window)
				ImGui::ShowDemoWindow(&show_demo_window);

			// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
			{
				static float f = 0.0f;
				static int counter = 0;

				ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

				ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
				ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
				ImGui::Checkbox("Another Window", &show_another_window);

				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

				if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
					counter++;
				ImGui::SameLine();
				ImGui::Text("counter = %d", counter);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::End();
			}

			// 3. Show another simple window.
			if (show_another_window)
			{
				ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
				ImGui::Text("Hello from another window!");
				if (ImGui::Button("Close Me"))
					show_another_window = false;
				ImGui::End();
			}

			ImGui::Begin("GameWindow");
			{
				// Using a Child allow to fill all the space of the window.
				// It also alows customization
				ImGui::BeginChild("GameRender");
				// Get the size of the child (i.e. the whole draw size of the windows).
				ImVec2 wsize = ImGui::GetWindowSize();
				// Because I use the texture from OpenGL, I need to invert the V from the UV.
				ImGui::Image((ImTextureID)tex, wsize, ImVec2(0, 1), ImVec2(1, 0));
				ImGui::EndChild();
			}
			ImGui::End();


			// Rendering
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		void HandleEvent(Core::Event& e) override
		{

		}

	private:
		unsigned int fbo;
		unsigned int tex;

		bool show_demo_window = true;
		bool show_another_window = false;
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