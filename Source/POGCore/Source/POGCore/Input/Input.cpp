#include "POGCorePCH.h"
#include "Input.h"

#include "POGCore/Application/Application.h"
#include "POGCore/Event/Events.h"

namespace POG::Core
{
	std::array<int, POG_MAX_KEY_VALUE> Input::KeyActions = std::array<int, POG_MAX_KEY_VALUE>();
	std::array<int, POG_MAX_KEY_VALUE> Input::KeyModifiers = std::array<int, POG_MAX_KEY_VALUE>();

	std::array<int, POG_MAX_MOUSE_VALUE> Input::MouseActions = std::array<int, POG_MAX_MOUSE_VALUE>();
	std::array<int, POG_MAX_MOUSE_VALUE> Input::MouseModifiers = std::array<int, POG_MAX_MOUSE_VALUE>();

	bool Input::ShouldResetMouseMovement = true;

	bool Input::MouseHasMoved = false;
	float Input::MouseX = 0.0f;
	float Input::MouseY = 0.0f;
	float Input::PrevMouseX = 0.0f;
	float Input::PrevMouseY = 0.0f;
	float Input::DeltaMouseX = 0.0f;
	float Input::DeltaMouseY = 0.0f;

	InputManager Input::GlobalInputManager(false);

	void Input::Init()
	{
		auto& mainEventBus = Application::GetInstance().GetMainEventBus();
		mainEventBus.Subscribe<RawKeyEvent>(OnKeyEvent);
		mainEventBus.Subscribe<RawMouseMoveEvent>(OnMouseMoveEvent);
		mainEventBus.Subscribe<RawMouseButtonEvent>(OnMouseButtonEvent);

		ResetKeys();
		ResetMouseMovement();
		ResetMouseDeltas();
		ResetMouseButtons();
	}

	bool Input::KeyPressed(int key, int mod)
	{
		return KeyActions[key] == POG_INPUT_PRESS && KeyModifiers[key] == mod;
	}

	bool Input::KeyReleased(int key, int mod)
	{
		return KeyActions[key] == POG_INPUT_RELEASE && KeyModifiers[key] == mod;
	}

	bool Input::KeyRepeated(int key, int mod)
	{
		return KeyActions[key] == POG_INPUT_REPEAT && KeyModifiers[key] == mod;
	}

	bool Input::MouseButtonPressed(int button, int mod)
	{
		return MouseActions[button] == POG_INPUT_PRESS && MouseModifiers[button] == mod;
	}

	bool Input::MouseButtonReleased(int button, int mod)
	{
		return MouseActions[button] == POG_INPUT_RELEASE && MouseModifiers[button] == mod;
	}

	void Input::AddInputCallback(InputCallback inputCallback)
	{
		GlobalInputManager.AddInputCallback(inputCallback);
	}

	void Input::AddAction(std::string name, InputInfo inputInfo)
	{
		GlobalInputManager.AddAction(name, inputInfo);
	}

	void Input::AddState(std::string name, InputInfo activeInputInfo, InputInfo inactiveInputInfo)
	{
		GlobalInputManager.AddState(name, activeInputInfo, inactiveInputInfo);
	}

	void Input::AddAxis(std::string name, InputInfo activeNegativeInputInfo, InputInfo inactiveNegativeInputInfo, InputInfo activePositiveInputInfo, InputInfo inactivePositiveInputInfo)
	{
		GlobalInputManager.AddAxis(name, activeNegativeInputInfo, inactiveNegativeInputInfo, activePositiveInputInfo, inactivePositiveInputInfo);
	}

	void Input::ResetKeys()
	{
		for (int i = 0; i < POG_MAX_KEY_VALUE; i++)
		{
			KeyActions[i] = POG_INPUT_NONE;
			KeyModifiers[i] = POG_MOD_NONE;
		}
	}

	void Input::OnKeyEvent(RawKeyEvent& e)
	{
		Input::KeyActions[e.key] = e.action;
		Input::KeyModifiers[e.key] = e.mods;

		GlobalInputManager.OnKeyEvent(e);
	}

	void Input::ResetMouseMovement()
	{
		ShouldResetMouseMovement = true;
	}

	void Input::ResetMouseDeltas()
	{
		DeltaMouseX = 0;
		DeltaMouseY = 0;
		MouseHasMoved = false;
	}

	void Input::SetMouseXY(float x, float y)
	{
		if (ShouldResetMouseMovement)
		{
			PrevMouseX = x;
			PrevMouseY = y;

			ShouldResetMouseMovement = false;
		}
		else
		{
			PrevMouseX = MouseX;
			PrevMouseY = MouseY;
		}

		MouseX = x;
		MouseY = y;
		DeltaMouseX += MouseX - PrevMouseX;
		DeltaMouseY += MouseY - PrevMouseY;
	}

	void Input::ResetMouseButtons()
	{
		for (int i = 0; i < POG_MAX_MOUSE_VALUE; i++)
		{
			MouseActions[i] = POG_INPUT_NONE;
			MouseModifiers[i] = POG_MOD_NONE;
		}
	}

	void Input::OnMouseMoveEvent(RawMouseMoveEvent& e)
	{
		MouseHasMoved = true;

		SetMouseXY(e.mouseX, e.mouseY);

		GlobalInputManager.OnMouseMoveEvent(e);
	}

	void Input::OnMouseButtonEvent(RawMouseButtonEvent& e)
	{
		Input::MouseActions[e.button] = e.action;
		Input::MouseModifiers[e.button] = e.mods;

		GlobalInputManager.OnMouseButtonEvent(e);
	}

	void Input::Dispatch(float dt)
	{
		GlobalInputManager.Dispatch(dt);
	}
}