#pragma once

#include "Event.h"

#include "POGCore/Input/Input.h"

namespace POG::Core
{
	POG_EVENT(InputEvent, Event)
	{
		const char* GetName() const override
		{
			return STRINGIFY(InputEvent);
		}
	};

	POG_EVENT(KeyEvent, InputEvent)
	{
		int key, scancode, action, mods;

		KeyEvent(int key, int scancode, int action, int mods)
			: key(key)
			, scancode(scancode)
			, action(action)
			, mods(mods)
		{
		}

		const char* GetName() const override
		{
			return STRINGIFY(KeyEvent);
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << "KEY:" << key << ", SCANCODE: " << scancode << ", ACTION: " << action << ", MODS: " << mods;
			return ss.str();
		}
	};

	POG_EVENT(MouseMoveEvent, InputEvent)
	{
		float mouseX, mouseY;

		MouseMoveEvent(float mouseX, float mouseY)
			: mouseX(mouseX)
			, mouseY(mouseY)
		{
		}

		const char* GetName() const override
		{
			return STRINGIFY(MouseMoveEvent);
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << "MouseX:" << Input::MouseX << ", MouseY: " << Input::MouseY;
			return ss.str();
		}
	};

	POG_EVENT(MouseButtonEvent, InputEvent)
	{
		int button, action, mods;

		MouseButtonEvent(int button, int action, int mods)
			: button(button)
			, action(action)
			, mods(mods)
		{
		}

		const char* GetName() const override
		{
			return STRINGIFY(MouseButtonEvent);
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << "BUTTON:" << button << ", ACTION: " << action << ", MODS: " << mods;
			return ss.str();
		}
	};
}