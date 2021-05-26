#pragma once

#include "POGLog.h"

#include <list>
#include <map>
#include <typeindex>
#include <typeinfo>
#include <vector>

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
		ZEvent()
			: isHandled(false)
		{
		}

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

		bool ConsistsOf(T* object, Handler handler) const
		{
			return this->object == object && this->handler == handler;
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
			size_t eventTypeIndex = Common::HashId<E>();
			std::vector<EventHandlerBase*>* handlers = subscribers[eventTypeIndex];
			
			if (!handlers)
			{
				return;
			}

			int& eventDepth = eventDepths[eventTypeIndex];
			std::vector<int>& eventHandlerIndexesToRemove = eventHandlersToRemove[eventTypeIndex];

			// Increase the depth whilst we process the event
			// If a handler publishes another of the same event on the same bus
			// This value will be incremented again and so on...
			eventDepth++;

			// Use a normal for loop to iterate through each handler
			// So we can compare indexes inside eventHandlersToRemove
			// To avoid calling event handlers that are being removed
			for (int i = 0; i < handlers->size() && !e->IsHandled(); i++)
			{
				// Check if this event handler is being removed
				if (eventHandlerIndexesToRemove.empty() || std::find(eventHandlerIndexesToRemove.begin(), eventHandlerIndexesToRemove.end(), i) == eventHandlerIndexesToRemove.end())
				{
					(*handlers)[i]->Handle(*e);
				}
			}

			// Once we've finished handling the event, decrease the depth
			eventDepth--;

			// If we have now finished handling the event
			// Remove any handlers that were set to be removed during the handling of the event
			if (eventDepth == 0 && !eventHandlerIndexesToRemove.empty())
			{
				std::sort(eventHandlerIndexesToRemove.begin(), eventHandlerIndexesToRemove.end());

				for (int i = 0; i < eventHandlerIndexesToRemove.size(); i++)
				{
					// Subtract i as the list shrinks for every removal
					int index = eventHandlerIndexesToRemove[i] - i;

					handlers->erase(handlers->begin() + index);
				}

				// Clear all the indexes as we should have removed them now
				eventHandlerIndexesToRemove.clear();
			}
		}

		template<class T, class E>
		void Subscribe(T* object, void (T::*handler)(E&))
		{
			POG_TRACE("Subscribing event handler: {0}", typeid(handler).name());

			size_t eventTypeIndex = Common::HashId<E>();
			std::vector<EventHandlerBase*>* handlers = subscribers[eventTypeIndex];

			// If handlers doesn't exist for this event type then create a new list
			if (!handlers)
			{
				handlers = new std::vector<EventHandlerBase*>();
				subscribers[eventTypeIndex] = handlers;
				eventDepths[eventTypeIndex] = 0;
			}

			handlers->push_back(new EventHandler(object, handler));
		}

		template<class T, class E>
		void Unsubscribe(T* object, void (T::*handler)(E&))
		{
			POG_TRACE("Unsubscribing event handler: {0}", typeid(handler).name());

			size_t eventTypeIndex = Common::HashId<E>();
			std::vector<EventHandlerBase*>* handlers = subscribers[eventTypeIndex];

			// If handlers doesn't exist for this event type then there's nothing to unsubscribe
			if (!handlers)
			{
				POG_WARN("Tried to unsubscribe event handler that didn't exist!");

				return;
			}

			int eventDepth = eventDepths[eventTypeIndex];

			// If we are not currently handling an event of this type we can just unsubscribe now
			if (eventDepth == 0)
			{
				auto it = handlers->begin();
				while (it != handlers->end())
				{
					EventHandler<T, E>* testHandler = static_cast<EventHandler<T, E>*>(*it);
					if (testHandler->ConsistsOf(object, handler))
					{
						it = handlers->erase(it);
					}
					else
					{
						it++;
					}
				}
			}
			// Otherwise make sure we don't remove it yet but make a note to once we've finished handling the root event
			else
			{
				for (int i = 0; i < handlers->size(); i++)
				{
					EventHandler<T, E>* testHandler = static_cast<EventHandler<T, E>*>((*handlers)[i]);
					if (testHandler->ConsistsOf(object, handler))
					{
						eventHandlersToRemove[eventTypeIndex].push_back(i);
					}
				}
			}
		}

	private:
		std::map<size_t, std::vector<EventHandlerBase*>*> subscribers;
		std::map<size_t, std::vector<int>> eventHandlersToRemove;
		std::map<size_t, int> eventDepths;
	};

	struct WindowCloseEvent : public ZEvent
	{
		const char* GetName() const override
		{
			return STRINGIFY(WindowCloseEvent);
		}
	};

	struct CursorEnabledEvent : public ZEvent
	{
		bool isCursorEnabled;

		CursorEnabledEvent(bool isCursorEnabled)
			: isCursorEnabled(isCursorEnabled)
		{
		}

		const char* GetName() const override
		{
			return STRINGIFY(CursorEnabledEvent);
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << isCursorEnabled;
			return ss.str();
		}
	};
}