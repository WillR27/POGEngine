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
}