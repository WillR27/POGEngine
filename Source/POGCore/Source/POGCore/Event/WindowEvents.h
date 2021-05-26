#pragma once

#include "Event.h"

namespace POG::Core
{
	struct WindowCloseEvent : public Event
	{
		const char* GetName() const override
		{
			return STRINGIFY(WindowCloseEvent);
		}
	};

	struct WindowSizeEvent : public Event
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

	struct WindowFocusEvent : public Event
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