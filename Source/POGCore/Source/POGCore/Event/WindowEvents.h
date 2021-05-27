#pragma once

#include "Event.h"

namespace POG::Core
{
	POG_EVENT(WindowCloseEvent, Event)
	{
		const char* GetName() const override
		{
			return STRINGIFY(WindowCloseEvent);
		}
	};

	POG_EVENT(WindowSizeEvent, Event)
	{
		int width, height;

		WindowSizeEvent(int width, int height)
			: width(width)
			, height(height)
		{
		}

		const char* GetName() const override
		{
			return STRINGIFY(WindowSizeEvent);
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << width << ", " << height;
			return ss.str();
		}
	};

	POG_EVENT(WindowFocusEvent, Event)
	{
		bool hasFocus;

		WindowFocusEvent(bool hasFocus)
			: hasFocus(hasFocus)
		{
		}

		const char* GetName() const override
		{
			return STRINGIFY(WindowFocusEvent);
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << hasFocus;
			return ss.str();
		}
	};
}