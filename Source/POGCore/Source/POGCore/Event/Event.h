#pragma once

#include <list>
#include <map>
#include <set>
#include <typeindex>
#include <typeinfo>
#include <vector>

#include "POGLog.h"
#include "POGUtil.h"

#define POG_EVENT(NewEvent, BaseEvent)	struct NewEvent; \
										static POG::Core::DerivedClasses<POG::Util::Hash<BaseEvent>()> POG_EVENT_##NewEvent(POG::Util::Hash<NewEvent>()); \
										struct NewEvent : public BaseEvent

namespace POG::Core
{
	// TODO: Move to generic location like POGUtil
	template<Util::HashId BaseClassId>
	class DerivedClasses
	{
	public:
		DerivedClasses(Util::HashId id)
		{
			if (DerivedIds == nullptr || DerivedIds->size() == 0)
			{
				DerivedIds = new std::vector<Util::HashId>();
			}

			if (std::find(DerivedIds->begin(), DerivedIds->end(), id) == DerivedIds->end())
			{
				DerivedIds->push_back(id);
			}
		}

		~DerivedClasses()
		{
			if (DerivedIds != nullptr)
			{
				delete DerivedIds;
				DerivedIds = nullptr;
			}
		}

		static std::vector<Util::HashId>* DerivedIds;
	};
	template<Util::HashId BaseClassId>
	std::vector<Util::HashId>* DerivedClasses<BaseClassId>::DerivedIds = nullptr;

	struct Event
	{
	public:
		Event()
			: isHandled(false)
		{
		}

		virtual ~Event() = default;

		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsHandled() { return isHandled; }
		void SetHandled() { this->isHandled = true; }

	private:
		bool isHandled;
	};

	class EventHandlerBase
	{
	public:
		virtual void Handle(Event& e) = 0;
	};

	template<class E>
	class EventHandler final : public EventHandlerBase
	{
	public:
		EventHandler(Util::Function<void(E&)> function)
			: function(function)
		{
		}

		virtual void Handle(Event& e)
		{
			function(static_cast<E&>(e));
		}

		bool Equals(const EventHandler<E> eventHandler)
		{
			return this->function.Equals(eventHandler.function);
		}

	private:
		Util::Function<void(E&)> function;
	};

	class EventBus final
	{
	public:
		EventBus() = default;
		EventBus(const EventBus&) = delete;
		EventBus(EventBus&&) = delete;

		~EventBus()
		{
			for (auto& pair : subscribers)
			{
				std::vector<EventHandlerBase*>* handlers = pair.second;

				while (!handlers->empty())
				{
					delete handlers->back();
					handlers->pop_back();
				}

				delete handlers;
			}
		}

		template<class E>
		void Publish(E e)
		{
			PublishExisting(e);
		}

		template<class E>
		void PublishExisting(E& e)
		{
			constexpr Util::HashId eventId = Util::Hash<E>();
			std::vector<EventHandlerBase*>* handlers = subscribers[eventId];
			
			if (!handlers)
			{
				return;
			}

			int& eventDepth = eventDepths[eventId];
			std::vector<int>& eventHandlerIndexesToRemove = eventHandlersToRemove[eventId];

			// Increase the depth whilst we process the event
			// If a handler publishes another of the same event on the same bus
			// This value will be incremented again and so on...
			eventDepth++;

			// Use a normal for loop to iterate through each handler
			// So we can compare indexes inside eventHandlersToRemove
			// To avoid calling event handlers that are being removed
			for (int i = 0; i < handlers->size() && !e.IsHandled(); i++)
			{
				// Check if this event handler is being removed
				if (eventHandlerIndexesToRemove.empty() || std::find(eventHandlerIndexesToRemove.begin(), eventHandlerIndexesToRemove.end(), i) == eventHandlerIndexesToRemove.end())
				{
					(*handlers)[i]->Handle(e);
				}
			}

			// Once we've finished handling the event, decrease the depth
			eventDepth--;

			// If we have now finished handling the event
			// Remove any handlers that were set to be removed during the handling of the event
			// And delete the event unless the user has specified otherwise
			if (eventDepth == 0)
			{
				if (!eventHandlerIndexesToRemove.empty())
				{
					std::sort(eventHandlerIndexesToRemove.begin(), eventHandlerIndexesToRemove.end());

					for (int i = 0; i < eventHandlerIndexesToRemove.size(); i++)
					{
						// Subtract i as the list shrinks for every removal
						int index = eventHandlerIndexesToRemove[i] - i;

						delete (*handlers)[index];
						handlers->erase(handlers->begin() + index);
					}

					// Clear all the indexes as we should have removed them now
					eventHandlerIndexesToRemove.clear();
				}
			}
		}

		template<class E>
		void Subscribe(void(*handler)(E&))
		{
			Subscribe(Util::Function<void(E&)>(handler));
		}

		template<class T, class E>
		void Subscribe(void(T::*handler)(E&), T* obj)
		{
			Subscribe<E>({ handler, obj });
		}

		template<class E>
		void Subscribe(Util::Function<void(E&)> handler)
		{
			POG_TRACE("Subscribing event handler: {0}", typeid(handler).name());

			constexpr Util::HashId eventId = Util::Hash<E>();
			Subscribe<E>(eventId, handler);

			if (DerivedClasses<eventId>::DerivedIds != nullptr)
			{
				for (auto derivedId : *DerivedClasses<eventId>::DerivedIds)
				{
					Subscribe(derivedId, handler);
				}
			}
		}

		template<class E>
		void Subscribe(Util::HashId eventId, Util::Function<void(E&)> handler)
		{
			std::vector<EventHandlerBase*>* handlers = subscribers[eventId];

			// If handlers doesn't exist for this event type then create a new list
			if (!handlers)
			{
				handlers = new std::vector<EventHandlerBase*>();
				subscribers[eventId] = handlers;
				eventDepths[eventId] = 0;
			}

			handlers->push_back(new EventHandler(handler));
		}

		template<class E>
		void Unsubscribe(void(*handler)(E&))
		{
			Unsubscribe(Util::Function<void(E&)>(handler));
		}

		template<class T, class E>
		void Unsubscribe(void(T::* handler)(E&), T* obj)
		{
			Unsubscribe<E>({ handler, obj });
		}

		template<class E>
		void Unsubscribe(Util::Function<void(E&)> handler)
		{
			POG_TRACE("Unsubscribing event handler: {0}", typeid(handler).name());

			constexpr Util::HashId eventId = Util::Hash<E>();
			std::vector<EventHandlerBase*>* handlers = subscribers[eventId];

			// If handlers doesn't exist for this event type then there's nothing to unsubscribe
			if (!handlers)
			{
				POG_WARN("Tried to unsubscribe event handler that didn't exist!");

				return;
			}

			int eventDepth = eventDepths[eventId];

			// If we are not currently handling an event of this type we can just unsubscribe now
			if (eventDepth == 0)
			{
				auto it = handlers->begin();
				while (it != handlers->end())
				{
					EventHandler<E>* testHandler = dynamic_cast<EventHandler<E>*>(*it);
					if (testHandler != nullptr && testHandler->Equals(handler))
					{
						delete* it;
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
					EventHandler<E>* testHandler = dynamic_cast<EventHandler<E>*>((*handlers)[i]);
					if (testHandler != nullptr && testHandler->Equals(handler))
					{
						eventHandlersToRemove[eventId].push_back(i);
					}
				}
			}
		}

	private:
		std::map<Util::HashId, std::vector<EventHandlerBase*>*> subscribers;
		std::map<Util::HashId, std::vector<int>> eventHandlersToRemove;
		std::map<Util::HashId, int> eventDepths;
	};
}