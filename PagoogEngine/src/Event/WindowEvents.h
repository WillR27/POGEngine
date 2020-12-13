#pragma once

#include "Event.h"

namespace PEngine
{
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		virtual const char* GetName() const override
		{
			return "WindowCloseEvent";
		}
	};

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
			return "WindowSizeEvent";
		}

		virtual std::string ToString() const override
		{ 
			std::stringstream ss;
			ss << GetName() << ": " << width << ", " << height;
			return ss.str();
		}
	};
}