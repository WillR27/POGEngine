#include "POGEditorPCH.h"
#include "POGEditor.h"

#include <filesystem>

#include "POGEditorScene.h"

#include "POGCore/Main.h"

namespace POG::Editor
{
	POGEditor* POGEditor::Instance = nullptr;

	POGEditor& POGEditor::GetInstance()
	{
		return *Instance;
	}

	POGEditor::POGEditor()
		: Application::Application("POG Editor")
		, exampleDll(nullptr)
		, createClientApplication(nullptr)
		, clientApplication(nullptr)
		, clientWorkspaceDirectory(std::filesystem::current_path().string())
		, isClientFocused(false)
		, isClientPaused(false)
		, wasCursorEnabled(true)
	{
		Instance = this;
	}

	POGEditor::~POGEditor()
	{
		delete clientApplication;
	}

	void POGEditor::Exit()
	{
		if (IsClientLoaded())
		{
			UnloadClient();
		}

		Application::Exit();
	}

	void POGEditor::Init()
	{
		//SetClientWorkspaceDirectory("F:\\Dev\\Projects\\Pagoog\\External\\POGEngine\\Source\\Example");

		SetTargetUpdatesPerSecond(60.0f);
		SetTargetFramesPerSecond(60.0f);

		GetMainEventBus().Subscribe(this, &POGEditor::OnInputEvent);
		GetMainEventBus().Subscribe(this, &POGEditor::OnKeyEvent);
		GetMainEventBus().Subscribe(this, &POGEditor::OnMouseButtonEvent);
		GetMainEventBus().Subscribe(this, &POGEditor::OnMouseMoveEvent);

		GetMainEventBus().Subscribe(this, &POGEditor::OnClientFocusedEvent);
		GetMainEventBus().Subscribe(this, &POGEditor::OnClientPlayEvent);
		GetMainEventBus().Subscribe(this, &POGEditor::OnClientPauseEvent);
		GetMainEventBus().Subscribe(this, &POGEditor::OnClientStopEvent);

		Core::Input::AddAction("Quit", Core::InputInfo(Core::InputType::Keyboard, POG_KEY_ESCAPE, POG_INPUT_RELEASE, POG_MOD_ANY));
		Core::Input::AddAction("Fullscreen", Core::InputInfo(Core::InputType::Keyboard, POG_KEY_F11, POG_INPUT_RELEASE, POG_MOD_ANY));

		Core::Scene::SetActiveScene(std::make_shared<POGEditorScene>());
	}

	void POGEditor::TryUpdate(float timeBetweenLoops)
	{
		Application::TryUpdate(timeBetweenLoops);

		if (IsClientLoaded() && !IsClientPaused())
		{
			clientApplication->TryUpdate(timeBetweenLoops);
		}
	}

	void POGEditor::TryFrame(float timeBetweenLoops)
	{
		if (IsClientLoaded() && !IsClientPaused())
		{
			clientApplication->TryFrame(timeBetweenLoops);
		}

		Application::TryFrame(timeBetweenLoops);

		if (IsClientLoaded() && !IsClientPaused())
		{
			if (clientApplication->HasUpdated())
			{
				clientApplication->ResetInput();
			}
		}
	}

	void POGEditor::Input(Core::InputPackage& inputPackage, float dt)
	{
		if (inputPackage.HasActionOccurred("Quit", true))
		{
			if (IsClientLoaded() && !IsCursorEnabled())
			{
				wasCursorEnabled = false;
				SetCursorEnabled(true);
			}
			else
			{
				Exit();
			}
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

	void POGEditor::OnInputEvent(Core::InputEvent& e)
	{
		if (IsClientLoaded() && !IsClientFocused())
		{
			e.SetHandled();
		}
	}

	void POGEditor::OnKeyEvent(Core::RawKeyEvent& e)
	{
		if (e.key == POG_KEY_ESCAPE || e.key == POG_KEY_F11)
		{
			
		}
	}

	void POGEditor::OnMouseButtonEvent(Core::RawMouseButtonEvent& e)
	{
	}

	void POGEditor::OnMouseMoveEvent(Core::RawMouseMoveEvent& e)
	{

	}

	void POGEditor::OnClientFocusedEvent(ClientFocusedEvent& e)
	{
		isClientFocused = e.isClientFocused;

		if (IsCursorEnabled() != wasCursorEnabled)
		{
			SetCursorEnabled(wasCursorEnabled);
		}
	}

	void POGEditor::OnClientPlayEvent(ClientPlayEvent& e)
	{
		if (!IsClientLoaded())
		{
			LoadClient();
			wasCursorEnabled = IsCursorEnabled();
		}
		else
		{
			// Reset the cursor back to what the client wanted before pausing if unpausing
			if (IsCursorEnabled() != wasCursorEnabled)
			{
				SetCursorEnabled(wasCursorEnabled);
			}
		}

		// Set the client window to focused so events get passed through
		GetMainEventBus().Publish(ClientFocusedEvent(true));

		isClientPaused = false;

		e.SetHandled();
	}

	void POGEditor::OnClientPauseEvent(ClientPauseEvent& e)
	{
		isClientPaused = true;

		e.SetHandled();
	}

	void POGEditor::OnClientStopEvent(ClientStopEvent& e)
	{
		if (IsClientLoaded())
		{
			UnloadClient();
		}

		// If the cursor is somehow not already enabled, enable it
		if (!IsCursorEnabled())
		{
			SetCursorEnabled(true);
		}

		e.SetHandled();
	}

	void POGEditor::LoadClient()
	{
		POG_INFO("Loading dll!");

		exampleDll = LoadLibrary(L"Example.dll");
		POG_ASSERT(exampleDll, "Dll failed to load!");

		createClientApplication = reinterpret_cast<CreateClientApplication>(GetProcAddress(exampleDll, "CreateClientApplication"));
		POG_ASSERT(createClientApplication, "Function not found!");

		clientApplication = createClientApplication();
		clientApplication->SetMainEventBus(GetMainEventBus());
		clientApplication->SetStandalone(false);
		clientApplication->SetContextAddressFunc(GetWindow().GetContextAddressFunc());
		clientApplication->PreInit();
		clientApplication->Init();
		clientApplication->PostInit();
	}

	void POGEditor::UnloadClient()
	{
		POG_INFO("Unloading dll!");

		clientApplication->Exit();
		clientApplication->Destroy();
		clientApplication = nullptr;

		FreeLibrary(exampleDll);

		SetCursorEnabled(true);
		isClientPaused = false;
	}
}

POG::Core::Application* POG::Core::CreateApplication()
{
	return new POG::Editor::POGEditor();
}