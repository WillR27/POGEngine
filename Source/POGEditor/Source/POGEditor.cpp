#include "POGEditorPCH.h"
#include "POGEditor.h"

#include "POGCore/Main.h"

#include "POGEditorScene.h"

#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace POG::Editor
{
	Core::IApplication* POGEditor::clientApplication = nullptr;

	POGEditor::POGEditor()
		: Application::Application("POG Example")
	{
	}

	POGEditor::~POGEditor()
	{
		delete clientFBO;
		delete clientTexture;

		delete clientApplication;
	}

	void POGEditor::Exit()
	{
		Application::Exit();
	}

	void POGEditor::Init()
	{
		inputManager->AddAction("Quit", Core::InputInfo(Core::InputType::Keyboard, PG_KEY_ESCAPE, PG_KEY_RELEASE, PG_MOD_ANY));
		inputManager->AddAction("Fullscreen", Core::InputInfo(Core::InputType::Keyboard, PG_KEY_F11, PG_KEY_RELEASE, PG_MOD_ANY));
		inputManager->AddAction("Load", Core::InputInfo(Core::InputType::Keyboard, PG_KEY_SPACE, PG_KEY_RELEASE, PG_MOD_ANY));

		activeScene = std::make_unique<POGEditorScene>();

		exampleDll = LoadLibrary(L"Example.dll");
		POG_ASSERT(exampleDll, "Dll failed to load!");

		createClientApplication = reinterpret_cast<CreateClientApplication>(
			GetProcAddress(exampleDll, "CreateClientApplication"));
		POG_ASSERT(createClientApplication, "Function not found!");

		clientApplication = createClientApplication();
		//clientApplication->window = this->window;
		//clientApplication->ownWindow = false;
		clientApplication->SetContextAddressFunc(GetWindow().GetContextAddressFunc());
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

		clientFBO = new Render::FrameBuffer();
		clientTexture = new Render::Texture();

		clientFBO->Bind();
		clientTexture->Bind();
		clientFBO->BindTexture(*clientTexture);
	}

	void POGEditor::Input(Core::InputPackage& inputPackage, float dt)
	{
		if (inputPackage.HasActionOccurred("Quit", true))
		{
			Exit();
		}

		if (inputPackage.HasActionOccurred("Fullscreen", true))
		{
			GetWindow().ToggleFullscreen();
		}

		static bool load = false;
		if (inputPackage.HasActionOccurred("Load", true))
		{
			if (load)
			{
				POG_TRACE("Loading dll!");
				exampleDll = LoadLibrary(L"Example.dll");
				POG_ASSERT(exampleDll, "Dll failed to load!");

				createClientApplication = reinterpret_cast<CreateClientApplication>(
					GetProcAddress(exampleDll, "CreateClientApplication"));
				POG_ASSERT(createClientApplication, "Function not found!");

				clientApplication = createClientApplication();
				//clientApplication->window = this->window;
				//clientApplication->ownWindow = false;
				clientApplication->SetContextAddressFunc(GetWindow().GetContextAddressFunc());
				clientApplication->PreInit();
				clientApplication->Init();
				clientApplication->PostInit();
			}
			else
			{
				POG_TRACE("Unloading dll!");
				clientApplication->Destroy();
				clientApplication = nullptr;
				FreeLibrary(exampleDll);
			}

			load = !load;
		}
	}

	void POGEditor::Update(float dt)
	{
		if (clientApplication)
		{
			clientApplication->Update(dt);
		}

		Application::Update(dt);
	}

	void POGEditor::Frame(float alpha)
	{
		clientFBO->Bind();
		clientTexture->Bind();
		clientFBO->BindTexture(*clientTexture);

		if (clientApplication)
		{
			clientApplication->Frame(alpha);
		}

		Application::Frame(alpha);
	}
}

POG::Core::Application* POG::Core::CreateApplication()
{
	return new POG::Editor::POGEditor();
}