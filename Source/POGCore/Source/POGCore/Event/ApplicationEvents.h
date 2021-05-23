#pragma once

#include "Event.h"

namespace POG::Core
{
	class CursorEnabledEvent : public Core::Event
	{
	public:
		bool isCursorEnabled;

		CursorEnabledEvent(bool isCursorEnabled)
			: isCursorEnabled(isCursorEnabled)
		{
		}

		virtual const char* GetName() const override
		{
			return STRINGIFY(CursorEnabledEvent);
		}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << isCursorEnabled;
			return ss.str();
		}
	};
}