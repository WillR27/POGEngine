#pragma once

#include "POGCore/Main.h"

#include "POGCore.h"
#include "POGRender.h"

#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Example.h"

namespace POG::Editor
{
	class POGEditorScene : public POG::Core::Scene
	{
	public:
		POGEditorScene() = default;

		virtual ~POGEditorScene() = default;

		void Init() override
		{
			const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

			const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

			shader.Init(vertexShaderSource, fragmentShaderSource);
		}

		void Input(Core::InputPackage& inputPackage, float dt) override
		{

		}

		void Update(float dt) override
		{

		}

		void Frame(float alpha) override;

		void HandleEvent(Core::Event& e) override
		{

		}

		void Exit() override
		{
			// Cleanup
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}

	private:
		Render::Shader shader;
		Render::VertexBuffer vbo;
		Render::VertexArray vao;

		bool show_demo_window = true;
		bool show_another_window = false;
	};

	class POGEditor : public POG::Core::Application
	{
	public:
		static Core::Application* clientApplication;

		POGEditor()
			: Application::Application("POG Example")
		{
		}

		virtual ~POGEditor()
		{
			delete clientApplication;
		}

		void Exit() override
		{
			glDeleteFramebuffers(1, &clientFBO);

			Application::Exit();
		}

		void Init() override
		{
			inputManager->AddAction("Quit", Core::InputInfo(Core::InputType::Keyboard, PG_KEY_ESCAPE, PG_KEY_RELEASE, PG_MOD_ANY));
			inputManager->AddAction("Fullscreen", Core::InputInfo(Core::InputType::Keyboard, PG_KEY_F11, PG_KEY_RELEASE, PG_MOD_ANY));

			activeScene = std::make_unique<POGEditorScene>();

			clientApplication = new Example::ExampleApplication();
			clientApplication->window = this->window;
			clientApplication->ownWindow = false;
			delete clientApplication->inputManager;
			clientApplication->inputManager = inputManager;
			clientApplication->PreInit();
			clientApplication->Init();
			clientApplication->PostInit();

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

			glGenFramebuffers(1, &clientFBO);
			glGenTextures(1, &clientTexture);

			glBindFramebuffer(GL_FRAMEBUFFER, clientFBO);
			glBindTexture(GL_TEXTURE_2D, clientTexture);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1000, 800, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, clientTexture, 0);
		}

		void Input(Core::InputPackage& inputPackage, float dt) override
		{
			if (inputPackage.HasActionOccurred("Quit", true))
			{
				Exit();
			}

			if (inputPackage.HasActionOccurred("Fullscreen", true))
			{
				GetWindow().ToggleFullscreen();
			}

			clientApplication->Input(inputPackage, dt);
		}

		void Update(float dt) override
		{
			clientApplication->Update(dt);

			Application::Update(dt);
		}

		void Frame(float alpha) override
		{
			glBindFramebuffer(GL_FRAMEBUFFER, clientFBO);
			glBindTexture(GL_TEXTURE_2D, clientTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GetWidth(), GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, clientTexture, 0);

			clientApplication->Frame(alpha);

			Application::Frame(alpha);
		}

		void Loop() override
		{
			Application::Loop();
		}

		unsigned int GetClientTexture() const { return clientTexture; }

	private:
		unsigned int clientFBO;
		unsigned int clientTexture;
	};

	Core::Application* POGEditor::clientApplication = nullptr;
}

std::unique_ptr<POG::Core::Application> POG::Core::CreateApplication()
{
	return std::make_unique<POG::Editor::POGEditor>();
}