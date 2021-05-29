#pragma once

#include "POGCore.h"

namespace POG::Editor
{
	POG_EVENT(ClientPlayEvent, Core::Event)
	{
		ClientPlayEvent()
		{
		}

		const char* GetName() const override
		{
			return STRINGIFY(ClientPlayEvent);
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName();
			return ss.str();
		}
	};

	POG_EVENT(ClientPauseEvent, Core::Event)
	{
		ClientPauseEvent()
		{
		}

		const char* GetName() const override
		{
			return STRINGIFY(ClientPauseEvent);
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName();
			return ss.str();
		}
	};

	POG_EVENT(ClientStopEvent, Core::Event)
	{
		ClientStopEvent()
		{
		}

		const char* GetName() const override
		{
			return STRINGIFY(ClientStopEvent);
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName();
			return ss.str();
		}
	};

	POG_EVENT(ClientFocusedEvent, Core::Event)
	{
		bool isClientFocused;

		ClientFocusedEvent(bool isClientFocused)
			: isClientFocused(isClientFocused)
		{
		}

		const char* GetName() const override
		{
			return STRINGIFY(ClientFocusedEvent);
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << isClientFocused;
			return ss.str();
		}
	};
}