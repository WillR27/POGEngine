#pragma once

#include "Event.h"
#include "Input/Input.h"

namespace PEngine
{
	class KeyEvent : public Event
	{
	public:
		int key, scancode, action, mods;

		KeyEvent(int key, int scancode, int action, int mods)
			: key(key)
			, scancode(scancode)
			, action(action)
			, mods(mods)
		{
		}

		virtual const char* GetName() const override
		{
			return STRINGIFY(KeyEvent);
		}

		virtual std::string ToString() const override
		{ 
			std::stringstream ss;
			ss << GetName() << ": " << "KEY:" << key << ", SCANCODE: " << scancode << ", ACTION: " << action << ", MODS: " << mods;
			return ss.str();
		}
	};

	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float mouseX, float mouseY)
		{
			if (Input::MouseX == -1.0f)
			{
				Input::PrevMouseX = mouseX;
				Input::PrevMouseY = mouseY;
				Input::MouseX = mouseX;
				Input::MouseY = mouseY;
			}
			else
			{
				Input::PrevMouseX = Input::MouseX;
				Input::PrevMouseY = Input::MouseY;
				Input::MouseX = mouseX;
				Input::MouseY = mouseY;
			}

			Input::DeltaMouseX += Input::PrevMouseX - Input::MouseX;
			Input::DeltaMouseY += Input::PrevMouseY - Input::MouseY;
		}

		virtual const char* GetName() const override
		{
			return STRINGIFY(MouseMoveEvent);
		}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << "MouseX:" << Input::MouseX << ", MouseY: " << Input::MouseY;
			return ss.str();
		}
	};
}