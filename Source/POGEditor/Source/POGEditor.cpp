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
		, isClientFocused(false)
		, isClientPaused(false)
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

		inputManager.AddAction("Quit", Core::InputInfo(Core::InputType::Keyboard, POG_KEY_ESCAPE, POG_KEY_RELEASE, POG_MOD_ANY));
		inputManager.AddAction("Fullscreen", Core::InputInfo(Core::InputType::Keyboard, POG_KEY_F11, POG_KEY_RELEASE, POG_MOD_ANY));

		activeScene = std::make_unique<POGEditorScene>();
	}

	void POGEditor::TryUpdate(float timeBetweenLoops)
	{
		if (IsClientLoaded() && !IsClientPaused())
		{
			clientApplication->TryUpdate(timeBetweenLoops);
		}

		Application::TryUpdate(timeBetweenLoops);
	}

	void POGEditor::TryFrame(float timeBetweenLoops)
	{
		if (IsClientLoaded() && !IsClientPaused())
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

		if (IsClientLoaded() && !IsClientPaused() && IsClientFocused())
		{
			clientApplication->HandleEvent(e);
		}
	}

	void POGEditor::TryLoadClient()
	{
		if (!IsClientLoaded())
		{
			LoadClient();
		}
	}

	void POGEditor::TryUnloadClient()
	{
		if (IsClientLoaded())
		{
			UnloadClient();
		}
	}

	void POGEditor::LoadClient()
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

	void POGEditor::UnloadClient()
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