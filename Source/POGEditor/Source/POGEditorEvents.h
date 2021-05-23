#pragma once

#include "POGCore.h"

namespace POG::Editor
{
	class ClientPlayEvent : public Core::Event
	{
	public:
		ClientPlayEvent()
		{
		}

		virtual const char* GetName() const override
		{
			return STRINGIFY(ClientPlayEvent);
		}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName();
			return ss.str();
		}
	};

	class ClientPauseEvent : public Core::Event
	{
	public:
		ClientPauseEvent()
		{
		}

		virtual const char* GetName() const override
		{
			return STRINGIFY(ClientPauseEvent);
		}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName();
			return ss.str();
		}
	};

	class ClientStopEvent : public Core::Event
	{
	public:
		ClientStopEvent()
		{
		}

		virtual const char* GetName() const override
		{
			return STRINGIFY(ClientStopEvent);
		}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName();
			return ss.str();
		}
	};

	class ClientFocusedEvent : public Core::Event
	{
	public:
		bool isClientFocused;

		ClientFocusedEvent(bool isClientFocused)
			: isClientFocused(isClientFocused)
		{
		}

		virtual const char* GetName() const override
		{
			return STRINGIFY(ClientFocusedEvent);
		}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << isClientFocused;
			return ss.str();
		}
	};
}