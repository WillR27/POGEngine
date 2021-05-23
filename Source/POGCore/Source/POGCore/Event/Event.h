#pragma once

#include <functional>
#include <ostream>
#include <sstream>
#include <string>

#include "POGCommon.h"

namespace POG::Core
{
	class Event
	{
	public:
		virtual ~Event() = default;

		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsHandled() const { return handled; }

	private:
		bool handled = false;

		friend class EventDispatcher;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e)
			: e(e)
		{
		}

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (!e.handled && (typeid(e) == typeid(T) || typeid(T) == typeid(Event)))
			{
				e.handled = func(static_cast<T&>(e));

				return true;
			}

			return false;
		}

	private:
		Event& e;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}

using EventCallback = std::function<void(POG::Core::Event&)>;