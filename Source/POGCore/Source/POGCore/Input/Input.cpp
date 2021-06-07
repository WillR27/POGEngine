#include "POGCorePCH.h"
#include "Input.h"

namespace POG::Core
{
	std::array<int, POG_MAX_KEY_VALUE> Input::KeyActions = std::array<int, POG_MAX_KEY_VALUE>();
	std::array<int, POG_MAX_KEY_VALUE> Input::KeyModifiers = std::array<int, POG_MAX_KEY_VALUE>();

	bool Input::ShouldResetMouseMovement = true;

	float Input::MouseX = 0.0f;
	float Input::MouseY = 0.0f;
	float Input::PrevMouseX = 0.0f;
	float Input::PrevMouseY = 0.0f;
	float Input::DeltaMouseX = 0.0f;
	float Input::DeltaMouseY = 0.0f;

	void Input::Init()
	{
		ResetKeys();
		ResetMouseMovement();
		ResetMouseDeltas();
	}

	bool Input::KeyPressed(int key, int mod)
	{
		return KeyActions[key] == POG_KEY_PRESS && KeyModifiers[key] == mod;
	}

	bool Input::KeyReleased(int key, int mod)
	{
		return KeyActions[key] == POG_KEY_RELEASE && KeyModifiers[key] == mod;
	}

	bool Input::KeyRepeated(int key, int mod)
	{
		return KeyActions[key] == POG_KEY_REPEAT && KeyModifiers[key] == mod;
	}

	void Input::ResetKeys()
	{
		for (int i = 0; i < POG_MAX_KEY_VALUE; i++)
		{
			KeyActions[i] = POG_KEY_EMPTY;
			KeyModifiers[i] = POG_MOD_NONE;
		}
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
}