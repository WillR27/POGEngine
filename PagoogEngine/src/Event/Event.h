#pragma once

namespace PEngine
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
			if (typeid(e) == typeid(T))
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
