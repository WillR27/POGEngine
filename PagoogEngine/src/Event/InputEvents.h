#pragma once

#include "Event.h"

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
			return "KeyEvent";
		}

		virtual std::string ToString() const override
		{ 
			std::stringstream ss;
			ss << GetName() << ": " << "KEY:" << key << ", SCANCODE: " << scancode << ", ACTION: " << action << ", MODS: " << mods;
			return ss.str();
		}
	};
}