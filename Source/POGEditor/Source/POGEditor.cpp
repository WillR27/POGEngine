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
		if (IsClientLoaded())
		{
			UnloadClient();
		}

		Application::Exit();
	}

	void POGEditor::Init()
	{
		SetTargetUpdatesPerSecond(60.0f);
		SetTargetFramesPerSecond(60.0f);

		GetInputManager().AddAction("Quit", Core::InputInfo(Core::InputType::Keyboard, POG_KEY_ESCAPE, POG_KEY_RELEASE, POG_MOD_ANY));
		GetInputManager().AddAction("Fullscreen", Core::InputInfo(Core::InputType::Keyboard, POG_KEY_F11, POG_KEY_RELEASE, POG_MOD_ANY));

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

	bool POGEditor::HandleEvent(Core::Event& e)
	{
		Core::EventDispatcher ed(e);
		ed.Dispatch<Core::KeyEvent>(POG_BIND_FN_THIS(LookForReservedKeys));
		ed.Dispatch<Core::MouseButtonEvent>(POG_BIND_FN_THIS(LookForReservedMouseButtons));

		ed.Dispatch<ClientFocusedEvent>(POG_BIND_FN_THIS(HandleClientFocusedEvent));
		ed.Dispatch<ClientPlayEvent>(POG_BIND_FN_THIS(HandleClientPlayEvent));
		ed.Dispatch<ClientPauseEvent>(POG_BIND_FN_THIS(HandleClientPauseEvent));
		ed.Dispatch<ClientStopEvent>(POG_BIND_FN_THIS(HandleClientStopEvent));

		ed.Dispatch<Core::CursorEnabledEvent>(POG_BIND_FN_THIS(HandleCursorEnabledEvent));

		// TODO: Remove WindowCloseEvent check
		// Prevent the WindowCloseEvent from handled in the client
		// As the client will be deleted before the calls have unwound
		if (IsClientLoaded() && !IsClientPaused() && IsClientFocused() && typeid(e) != typeid(Core::WindowCloseEvent))
		{
			ed.Dispatch<Core::Event>(POG_BIND_FN_THIS(clientApplication->HandleEvent));
		}

		ed.Dispatch<Core::Event>(POG_BIND_FN_THIS(Application::HandleEvent));

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

		if (IsCursorEnabled() != wasCursorEnabled)
		{
			SetCursorEnabled(wasCursorEnabled);
		}

		return false;
	}

	bool POGEditor::HandleClientPlayEvent(ClientPlayEvent& e)
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
		ClientFocusedEvent e2(true);
		HandleEvent(e2);

		isClientPaused = false;

		return true;
	}

	bool POGEditor::HandleClientPauseEvent(ClientPauseEvent& e)
	{
		isClientPaused = true;

		return true;
	}

	bool POGEditor::HandleClientStopEvent(ClientStopEvent& e)
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

		return true;
	}

	bool POGEditor::HandleCursorEnabledEvent(Core::CursorEnabledEvent& e)
	{
		Application::HandleCursorEnabledEvent(e);

		return false;
	}

	void POGEditor::LoadClient()
	{
		POG_INFO("Loading dll!");

		exampleDll = LoadLibrary(L"Example.dll");
		POG_ASSERT(exampleDll, "Dll failed to load!");

		createClientApplication = reinterpret_cast<CreateClientApplication>(GetProcAddress(exampleDll, "CreateClientApplication"));
		POG_ASSERT(createClientApplication, "Function not found!");

		clientApplication = createClientApplication();
		clientApplication->SetEditorEventHandler(POG_BIND_FN_THIS(HandleEvent));
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