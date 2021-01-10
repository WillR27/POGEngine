#include "pgepch.h"
#include "Input.h"

#include "Event/InputEvents.h"

namespace PEngine
{
	double Input::MouseX = 0.0;
	double Input::MouseY = 0.0;
	double Input::PrevMouseX = 0.0;
	double Input::PrevMouseY = 0.0;
	double Input::DeltaMouseX = 0.0;
	double Input::DeltaMouseY = 0.0;


	double Input::GetMouseX()
	{
		return MouseX;
	}

	double Input::GetMouseY()
	{
		return MouseY;
	}

	double Input::GetPrevMouseX()
	{
		return PrevMouseX;
	}

	double Input::GetPrevMouseY()
	{
		return PrevMouseY;
	}
}