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
	POGEditor::POGEditor()
		: Application::Application("POG Editor")
		, clientApplication(nullptr)
		, clientInputManager(nullptr)
	{
	}

	POGEditor::~POGEditor()
	{
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
		inputManager->AddAction("Load", Core::InputInfo(Core::InputType::Keyboard, PG_KEY_SPACE, PG_KEY_RELEASE, PG_MOD_NONE));

		activeScene = std::make_unique<POGEditorScene>();

		LoadClientApp();

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
				LoadClientApp();
			}
			else
			{
				UnloadClientApp();
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
		if (clientApplication)
		{
			clientApplication->Frame(alpha);
		}

		Application::Frame(alpha);
	}

	void POGEditor::HandleEvent(Core::Event& e)
	{
		if (IsClientLoaded())
		{
			clientApplication->HandleEvent(e);
		}

		Application::HandleEvent(e);
	}

	void POGEditor::LoadClientApp()
	{
		POG_INFO("Loading dll!");

		exampleDll = LoadLibrary(L"Example.dll");
		POG_ASSERT(exampleDll, "Dll failed to load!");

		createClientApplication = reinterpret_cast<CreateClientApplication>(GetProcAddress(exampleDll, "CreateClientApplication"));
		POG_ASSERT(createClientApplication, "Function not found!");

		clientInputManager = new Core::InputManager();

		clientApplication = createClientApplication();
		clientApplication->SetStandalone(false);
		clientApplication->SetInputManager(clientInputManager);
		clientApplication->SetContextAddressFunc(GetWindow().GetContextAddressFunc());
		clientApplication->PreInit();
		clientApplication->Init();
		clientApplication->PostInit();
	}

	void POGEditor::UnloadClientApp()
	{
		POG_INFO("Unloading dll!");

		clientApplication->Destroy();
		clientApplication = nullptr;

		delete clientInputManager;
		clientInputManager = nullptr;

		FreeLibrary(exampleDll);
	}
}

POG::Core::Application* POG::Core::CreateApplication()
{
	return new POG::Editor::POGEditor();
}