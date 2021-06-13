#pragma once

#include "POGMaths.h"

#include "Event.h"

namespace POG::Core
{
	POG_EVENT(InputEvent, Event)
	{
		const char* GetName() const override
		{
			return STRINGIFY(InputEvent);
		}
	};

	POG_EVENT(RawKeyEvent, InputEvent)
	{
		int key, scancode, action, mods;

		RawKeyEvent(int key, int scancode, int action, int mods)
			: key(key)
			, scancode(scancode)
			, action(action)
			, mods(mods)
		{
		}

		const char* GetName() const override
		{
			return STRINGIFY(RawKeyEvent);
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << "KEY:" << key << ", SCANCODE: " << scancode << ", ACTION: " << action << ", MODS: " << mods;
			return ss.str();
		}
	};

	POG_EVENT(RawMouseMoveEvent, InputEvent)
	{
		Maths::Vec2 pos;

		RawMouseMoveEvent(Maths::Vec2 pos)
			: pos(pos)
		{
		}

		const char* GetName() const override
		{
			return STRINGIFY(RawMouseMoveEvent);
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << "MouseX:" << pos.x << ", MouseY: " << pos.y;
			return ss.str();
		}
	};

	POG_EVENT(RawMouseButtonEvent, InputEvent)
	{
		int button, action, mods;

		RawMouseButtonEvent(int button, int action, int mods)
			: button(button)
			, action(action)
			, mods(mods)
		{
		}

		const char* GetName() const override
		{
			return STRINGIFY(RawMouseButtonEvent);
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << "BUTTON:" << button << ", ACTION: " << action << ", MODS: " << mods;
			return ss.str();
		}
	};
}