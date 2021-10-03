#pragma once

#include "POGCore/Event/Event.h"

namespace POG::Core
{
	POG_EVENT(ControlEvent, Event)
	{
		const char* GetName() const override
		{
			return STRINGIFY(ControlEvent);
		}
	};

	POG_EVENT(MousePressEvent, ControlEvent)
	{
		int button;

		MousePressEvent(int button)
			: button(button)
		{
		}

		const char* GetName() const override
		{
			return STRINGIFY(MousePressEvent);
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << "BUTTON:" << button;
			return ss.str();
		}
	};

	POG_EVENT(MouseReleaseEvent, ControlEvent)
	{
		int button;

		MouseReleaseEvent(int button)
			: button(button)
		{
		}

		const char* GetName() const override
		{
			return STRINGIFY(MouseReleaseEvent);
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << "BUTTON:" << button;
			return ss.str();
		}
	};

	POG_EVENT(KeyPressEvent, ControlEvent)
	{
		int key;
		int mods;

		KeyPressEvent(int key, int mods)
			: key(key)
			, mods(mods)
		{
		}

		const char* GetName() const override
		{
			return STRINGIFY(KeyPressEvent);
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << "KEY:" << key << ", MODS: " << mods;
			return ss.str();
		}
	};

	POG_EVENT(KeyReleaseEvent, ControlEvent)
	{
		int key;
		int mods;

		KeyReleaseEvent(int key, int mods)
			: key(key)
			, mods(mods)
		{
		}

		const char* GetName() const override
		{
			return STRINGIFY(KeyReleaseEvent);
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << "KEY:" << key << ", MODS: " << mods;
			return ss.str();
		}
	};

	POG_EVENT(KeyRepeatEvent, ControlEvent)
	{
		int key;
		int mods;

		KeyRepeatEvent(int key, int mods)
			: key(key)
			, mods(mods)
		{
		}

		const char* GetName() const override
		{
			return STRINGIFY(KeyRepeatEvent);
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << "KEY:" << key << ", MODS: " << mods;
			return ss.str();
		}
	};
}