#pragma once

#include "Event.h"

namespace Pagoog::Core
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
			//Input::SetMouseXY(mouseX, mouseY);
		}

		virtual const char* GetName() const override
		{
			return STRINGIFY(MouseMoveEvent);
		}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << "MouseX:" /*<< Input::MouseX << ", MouseY: " << Input::MouseY*/;
			return ss.str();
		}
	};

	class MouseButtonEvent : public Event
	{
	public:
		int button, action, mods;

		MouseButtonEvent(int button, int action, int mods)
			: button(button)
			, action(action)
			, mods(mods)
		{
		}

		virtual const char* GetName() const override
		{
			return STRINGIFY(MouseButtonEvent);
		}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << "BUTTON:" << button << ", ACTION: " << action << ", MODS: " << mods;
			return ss.str();
		}
	};
}