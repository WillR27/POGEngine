#pragma once

#include "POGCore.h"

namespace POG::Editor
{
	struct ClientPlayEvent : public Core::Event
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

	struct ClientPauseEvent : public Core::Event
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

	struct ClientStopEvent : public Core::Event
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

	struct ClientFocusedEvent : public Core::Event
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