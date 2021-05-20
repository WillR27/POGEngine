#include "POGEditorPCH.h"
#include "POGEditor.h"

#include "POGCore/Main.h"

#include "POGEditorScene.h"

namespace POG::Editor
{
	POGEditor::POGEditor()
		: Application::Application("POG Editor")
		, exampleDll(nullptr)
		, createClientApplication(nullptr)
		, clientApplication(nullptr)
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
		SetTargetUpdatesPerSecond(60.0f);
		SetTargetFramesPerSecond(60.0f);

		inputManager.AddAction("Quit", Core::InputInfo(Core::InputType::Keyboard, PG_KEY_ESCAPE, PG_KEY_RELEASE, PG_MOD_ANY));
		inputManager.AddAction("Fullscreen", Core::InputInfo(Core::InputType::Keyboard, PG_KEY_F11, PG_KEY_RELEASE, PG_MOD_ANY));
		inputManager.AddAction("Load", Core::InputInfo(Core::InputType::Keyboard, PG_KEY_SPACE, PG_KEY_RELEASE, PG_MOD_NONE));

		activeScene = std::make_unique<POGEditorScene>();

		LoadClientApp();
	}

	void POGEditor::TryUpdate(float timeBetweenLoops)
	{
		if (clientApplication)
		{
			clientApplication->TryUpdate(timeBetweenLoops);
		}

		Application::TryUpdate(timeBetweenLoops);
	}

	void POGEditor::TryFrame(float timeBetweenLoops)
	{
		if (clientApplication)
		{
			clientApplication->TryFrame(timeBetweenLoops);
		}

		Application::TryFrame(timeBetweenLoops);
	}

	void POGEditor::Input(Core::InputPackage& inputPackage, float dt)
	{
		if (inputPackage.HasActionOccurred("Quit", true))
		{
			Exit();
		}

		if (inputPackage.HasActionOccurred("Fullscreen", true))
		{
			ToggleFullscreen();
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
		Application::Update(dt);
	}

	void POGEditor::Frame(float alpha)
	{
		Application::Frame(alpha);
	}

	void POGEditor::HandleEvent(Core::Event& e)
	{
		Application::HandleEvent(e);

		if (IsClientLoaded())
		{
			clientApplication->HandleEvent(e);
		}
	}

	void POGEditor::LoadClientApp()
	{
		POG_INFO("Loading dll!");

		exampleDll = LoadLibrary(L"Example.dll");
		POG_ASSERT(exampleDll, "Dll failed to load!");

		createClientApplication = reinterpret_cast<CreateClientApplication>(GetProcAddress(exampleDll, "CreateClientApplication"));
		POG_ASSERT(createClientApplication, "Function not found!");

		clientApplication = createClientApplication();
		clientApplication->SetStandalone(false);
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

		FreeLibrary(exampleDll);
	}
}

POG::Core::Application* POG::Core::CreateApplication()
{
	return new POG::Editor::POGEditor();
}