#pragma once

#include "POGCore/Event/Event.h"

namespace POG::Core
{
	struct CursorEnabledEvent : public Event
	{
		bool isCursorEnabled;

		CursorEnabledEvent(bool isCursorEnabled)
			: isCursorEnabled(isCursorEnabled)
		{
		}

		const char* GetName() const override
		{
			return STRINGIFY(CursorEnabledEvent);
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << isCursorEnabled;
			return ss.str();
		}
	};
}