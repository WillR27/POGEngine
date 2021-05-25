#pragma once

#include "Event.h"

namespace POG::Core
{
	class WindowSizeEvent : public Event
	{
	public:
		int width, height;

		WindowSizeEvent(int width, int height)
			: width(width)
			, height(height)
		{
		}

		virtual const char* GetName() const override
		{
			return STRINGIFY(WindowSizeEvent);
		}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << width << ", " << height;
			return ss.str();
		}
	};

	class WindowFocusEvent : public Event
	{
	public:
		bool hasFocus;

		WindowFocusEvent(bool hasFocus)
			: hasFocus(hasFocus)
		{
		}

		virtual const char* GetName() const override
		{
			return STRINGIFY(WindowFocusEvent);
		}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << hasFocus;
			return ss.str();
		}
	};
}