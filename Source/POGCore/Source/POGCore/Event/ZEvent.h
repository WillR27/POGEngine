#pragma once

#include "POGLog.h"

#include <list>
#include <map>
#include <typeindex>
#include <typeinfo>

namespace POG::Core
{
	// Event buses that you can publish/subscribe to
	// mainBus.publish(new EggEvent())
	// mainBus.subscribe(egg->OnEgg)

	// Event handlers that are a wrapper around callback functions

	// Events that contain event data but not functionality

	class ZEvent
	{
	public:
		ZEvent() = default;

		virtual ~ZEvent() = default;

		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsHandled() { return isHandled; }
		void SetHandled(bool isHandled = true) { this->isHandled = isHandled; }

	private:
		bool isHandled;
	};

	class EventHandlerBase
	{
	public:
		void Handle(ZEvent& e)
		{
			POG_TRACE("Handling: {0}", e.ToString());

			Call(e);
		}

	private:
		virtual void Call(ZEvent& e) = 0;
	};

	template<class T, class E>
	class EventHandler : public EventHandlerBase
	{
	public:
		using Handler = void (T::*)(E&);

		EventHandler(T* object, Handler handler)
			: object(object)
			, handler(handler)
		{
		}

	private:
		T* object;
		Handler handler;

		void Call(ZEvent& e) override
		{
			(object->*handler)(static_cast<E&>(e));
		}
	};

	class EventBus final
	{
	public:
		EventBus() = default;
		EventBus(const EventBus&) = delete;
		EventBus(EventBus&&) = delete;

		~EventBus() = default;

		template<class E>
		void Publish(E* e)
		{
			std::list<EventHandlerBase*>* handlers = subscribers[typeid(E)];

			if (!handlers)
			{
				return;
			}

			for (auto& handler : *handlers)
			{
				if (!e->IsHandled())
				{
					handler->Handle(*e);
				}
			}
		}

		template<class T, class E>
		void Subscribe(T* object, void (T::*handler)(E&))
		{
			std::list<EventHandlerBase*>* handlers = subscribers[typeid(E)];

			// If handlers doesn't exist for this event type then create a new list
			if (!handlers)
			{
				handlers = new std::list<EventHandlerBase*>();
				subscribers[typeid(E)] = handlers;
			}

			handlers->push_back(new EventHandler(object, handler));
		}

	private:
		std::map<std::type_index, std::list<EventHandlerBase*>*> subscribers;
	};

	struct ZWindowCloseEvent : public ZEvent
	{
		const char* GetName() const override
		{
			return STRINGIFY(ZWindowCloseEvent);
		}
	};
}