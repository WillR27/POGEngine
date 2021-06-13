#include "POGCorePCH.h"
#include "Mouse.h"

#include "POGCore/Application/Application.h"
#include "POGCore/Event/Events.h"

#include "Input.h"

namespace POG::Core
{
	std::array<int, POG_MAX_MOUSE_VALUE> Mouse::MouseActions = std::array<int, POG_MAX_MOUSE_VALUE>();
	std::array<int, POG_MAX_MOUSE_VALUE> Mouse::MouseModifiers = std::array<int, POG_MAX_MOUSE_VALUE>();

	bool Mouse::ShouldResetMouseMovement = true;
	
	bool Mouse::MouseHasMoved = false;
	float Mouse::MouseX = 0.0f;
	float Mouse::MouseY = 0.0f;
	float Mouse::PrevMouseX = 0.0f;
	float Mouse::PrevMouseY = 0.0f;
	float Mouse::DeltaMouseX = 0.0f;
	float Mouse::DeltaMouseY = 0.0f;

	void Mouse::Init()
	{
		auto& mainEventBus = Application::GetInstance().GetMainEventBus();
		mainEventBus.Subscribe(OnRawMouseMoveEvent);
		mainEventBus.Subscribe(OnRawMouseButtonEvent);

		ResetMovement();
		ResetDeltas();
		ResetButtons();
	}

	void Mouse::OnRawMouseMoveEvent(RawMouseMoveEvent& e)
	{
		MouseHasMoved = true;

		SetXY(e.mouseX, e.mouseY);

		Input::GlobalInputManager.OnMouseMoveEvent(e);
	}

	void Mouse::OnRawMouseButtonEvent(RawMouseButtonEvent& e)
	{
		Mouse::MouseActions[e.button] = e.action;
		Mouse::MouseModifiers[e.button] = e.mods;

		Input::GlobalInputManager.OnMouseButtonEvent(e);
	}

	float Mouse::NormaliseMouseX()
	{
		return ((GetX() * 2.0f) / Core::Application::GetInstance().GetWidth()) - 1.0f;
	}

	float Mouse::NormaliseMouseY()
	{
		return ((GetY() * 2.0f) / Core::Application::GetInstance().GetHeight()) - 1.0f;
	}

	bool Mouse::IsButtonPressed(int button, int mod)
	{
		return MouseActions[button] == POG_INPUT_PRESS && MouseModifiers[button] == mod;
	}

	bool Mouse::IsButtonReleased(int button, int mod)
	{
		return MouseActions[button] == POG_INPUT_RELEASE && MouseModifiers[button] == mod;
	}

	void Mouse::SetXY(float x, float y)
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

	void Mouse::ResetMovement()
	{
		ShouldResetMouseMovement = true;
	}

	void Mouse::ResetDeltas()
	{
		DeltaMouseX = 0;
		DeltaMouseY = 0;
		MouseHasMoved = false;
	}

	void Mouse::ResetButtons()
	{
		for (int i = 0; i < POG_MAX_MOUSE_VALUE; i++)
		{
			MouseActions[i] = POG_INPUT_NONE;
			MouseModifiers[i] = POG_MOD_NONE;
		}
	}
}