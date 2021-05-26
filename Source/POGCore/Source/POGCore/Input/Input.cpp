#include "POGCorePCH.h"
#include "Input.h"

namespace POG::Core
{
	bool Input::ShouldResetMouseMovement = true;

	float Input::MouseX = 0.0f;
	float Input::MouseY = 0.0f;
	float Input::PrevMouseX = 0.0f;
	float Input::PrevMouseY = 0.0f;
	float Input::DeltaMouseX = 0.0f;
	float Input::DeltaMouseY = 0.0f;


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