#include "POGEditorPCH.h"
#include "POGEditor.h"

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
		TryUnloadClient();

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

	bool POGEditor::HandleEvent(Core::Event& e)
	{
		Core::EventDispatcher ed(e);
		ed.Dispatch<Core::KeyEvent>(POG_BIND_FN(LookForReservedKeys));
		ed.Dispatch<Core::MouseButtonEvent>(POG_BIND_FN(LookForReservedMouseButtons));

		ed.Dispatch<ClientFocusedEvent>(POG_BIND_FN(HandleClientFocusedEvent));
		ed.Dispatch<ClientPlayEvent>(POG_BIND_FN(HandleClientPlayEvent));
		ed.Dispatch<ClientPauseEvent>(POG_BIND_FN(HandleClientPauseEvent));
		ed.Dispatch<ClientStopEvent>(POG_BIND_FN(HandleClientStopEvent));

		ed.Dispatch<Core::CursorEnabledEvent>(POG_BIND_FN(HandleCursorEnabledEvent));

		if (IsClientLoaded() && !IsClientPaused() && IsClientFocused())
		{
			ed.Dispatch<Core::Event>(POG_BIND_FN(clientApplication->HandleEvent));
		}

		ed.Dispatch<Core::Event>(POG_BIND_FN(Application::HandleEvent));

		return false;
	}

	bool POGEditor::LookForReservedKeys(Core::KeyEvent& e)
	{
		if (e.key == POG_KEY_ESCAPE || e.key == POG_KEY_F11)
		{
			Application::HandleEvent(e);
		}

		return false;
	}

	bool POGEditor::LookForReservedMouseButtons(Core::MouseButtonEvent& e)
	{
		return false;
	}

	bool POGEditor::HandleClientFocusedEvent(ClientFocusedEvent& e)
	{
		isClientFocused = e.isClientFocused;

		return true;
	}

	bool POGEditor::HandleClientPlayEvent(ClientPlayEvent& e)
	{
		bool wasClientLoaded = IsClientLoaded();

		TryLoadClient();

		isClientPaused = false;

		// Reset the cursor back to what the client wanted before pausing if unpausing
		if (wasClientLoaded && IsCursorEnabled() != wasCursorEnabled)
		{
			SetCursorEnabled(wasCursorEnabled);
		}

		return true;
	}

	bool POGEditor::HandleClientPauseEvent(ClientPauseEvent& e)
	{
		isClientPaused = true;
		wasCursorEnabled = IsCursorEnabled();

		return true;
	}

	bool POGEditor::HandleClientStopEvent(ClientStopEvent& e)
	{
		TryUnloadClient();

		// If the cursor is somehow not already enabled, enable it
		if (!IsCursorEnabled())
		{
			SetCursorEnabled(true);
		}

		return true;
	}

	bool POGEditor::HandleCursorEnabledEvent(Core::CursorEnabledEvent& e)
	{
		Application::HandleCursorEnabledEvent(e);

		return false;
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
		clientApplication->SetEditorEventHandler(POG_BIND_FN(HandleEvent));
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

		SetCursorEnabled(true);
		isClientPaused = false;
	}
}

POG::Core::Application* POG::Core::CreateApplication()
{
	return new POG::Editor::POGEditor();
}