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
	Maths::Vec2 Mouse::Pos(0.0f, 0.0f);
	Maths::Vec2 Mouse::PrevPos(0.0f, 0.0f);
	Maths::Vec2 Mouse::DeltaPos(0.0f, 0.0f);

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

		SetPos(e.pos);

		Input::GlobalInputManager.OnMouseMoveEvent(e);
	}

	void Mouse::OnRawMouseButtonEvent(RawMouseButtonEvent& e)
	{
		Mouse::MouseActions[e.button] = e.action;
		Mouse::MouseModifiers[e.button] = e.mods;

		Input::GlobalInputManager.OnMouseButtonEvent(e);
	}

	Maths::Vec2 Mouse::Normalise(Maths::Vec2 min, Maths::Vec2 max)
	{
		Maths::Vec2 dif = max - min;

		float x = ((GetX() * dif.x) / Core::Application::GetInstance().GetWidth()) - (dif.x / 2.0f);
		float y = ((GetY() * dif.y) / Core::Application::GetInstance().GetHeight()) - (dif.y / 2.0f);

		return { x, y };
	}

	float Mouse::AngleFromXAxis(Maths::Vec2 normalisedOrigin)
	{
		Maths::Vec2 pos = Normalise() - normalisedOrigin;

		float angle = atan2f(pos.y, pos.x);

		return angle;
	}

	bool Mouse::IsButtonPressed(int button, int mod)
	{
		return MouseActions[button] == POG_INPUT_PRESS && MouseModifiers[button] == mod;
	}

	bool Mouse::IsButtonReleased(int button, int mod)
	{
		return MouseActions[button] == POG_INPUT_RELEASE && MouseModifiers[button] == mod;
	}

	void Mouse::SetPos(Maths::Vec2 mousePos)
	{
		if (ShouldResetMouseMovement)
		{
			PrevPos = mousePos;

			ShouldResetMouseMovement = false;
		}
		else
		{
			PrevPos = Pos;
		}

		Pos = mousePos;
		DeltaPos += (Pos - PrevPos);
	}

	void Mouse::ResetMovement()
	{
		ShouldResetMouseMovement = true;
	}

	void Mouse::ResetDeltas()
	{
		DeltaPos = Maths::Vec2(0.0f, 0.0f);
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