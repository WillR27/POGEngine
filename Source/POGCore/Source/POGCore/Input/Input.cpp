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

	float Input::MouseX = 0.0f;
	float Input::MouseY = 0.0f;
	float Input::PrevMouseX = 0.0f;
	float Input::PrevMouseY = 0.0f;
	float Input::DeltaMouseX = 0.0f;
	float Input::DeltaMouseY = 0.0f;

	void Input::Init()
	{
		auto& mainEventBus = Application::GetInstance().GetMainEventBus();
		mainEventBus.Subscribe(OnKeyEvent);
		mainEventBus.Subscribe(OnMouseMoveEvent);
		mainEventBus.Subscribe(OnMouseButtonEvent);

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

	void Input::ResetKeys()
	{
		for (int i = 0; i < POG_MAX_KEY_VALUE; i++)
		{
			KeyActions[i] = POG_INPUT_NONE;
			KeyModifiers[i] = POG_MOD_NONE;
		}
	}

	void Input::OnKeyEvent(KeyEvent& e)
	{
		Input::KeyActions[e.key] = e.action;
		Input::KeyModifiers[e.key] = e.mods;
	}

	void Input::ResetMouseMovement()
	{
		ShouldResetMouseMovement = true;
	}

	void Input::ResetMouseDeltas()
	{
		DeltaMouseX = 0;
		DeltaMouseY = 0;
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

	void Input::OnMouseMoveEvent(MouseMoveEvent& e)
	{
		SetMouseXY(e.mouseX, e.mouseY);
	}

	void Input::OnMouseButtonEvent(MouseButtonEvent& e)
	{
		Input::MouseActions[e.button] = e.action;
		Input::MouseModifiers[e.button] = e.mods;
	}
}