#include "pgepch.h"
#include "Input.h"

#include "Event/InputEvents.h"

namespace PEngine
{
	float Input::MouseX = -1.0f;
	float Input::MouseY = 0.0f;
	float Input::PrevMouseX = 0.0f;
	float Input::PrevMouseY = 0.0f;
	float Input::DeltaMouseX = 0.0f;
	float Input::DeltaMouseY = 0.0f;


	float Input::GetMouseX()
	{
		return MouseX;
	}

	float Input::GetMouseY()
	{
		return MouseY;
	}

	float Input::GetPrevMouseX()
	{
		return PrevMouseX;
	}

	float Input::GetPrevMouseY()
	{
		return PrevMouseY;
	}

	float Input::GetDeltaMouseX()
	{
		return DeltaMouseX;
	}

	float Input::GetDeltaMouseY()
	{
		return DeltaMouseY;
	}
}