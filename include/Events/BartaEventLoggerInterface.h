#pragma once
#include "../pch.h"
#include "Events/Events/MouseMoveEvent.h"
#include "Events/KeyPressedEvent.h"
#include "Events/KeyReleasedEvent.h"
#include "Events/LeftClickEvent.h"
#include "Events/VelocityChangeEvent.h"

namespace Barta {
	template<typename EventType, typename ... OtherTypes>
	class EventMatcher:public EventMatcher<EventType>, public EventMatcher<OtherTypes...> {
		public:
        EventMatcher() : EventMatcher<EventType>(), EventMatcher<OtherTypes...>() {}
		using EventMatcher<EventType>::logEvent;
		using EventMatcher<OtherTypes...>::logEvent;
		using EventMatcher<EventType>::logSubscriber;
		using EventMatcher<OtherTypes...>::logSubscriber;

		void runSubscribers() {
			EventMatcher<EventType>::runSubscribers();
			EventMatcher<OtherTypes...>::runSubscribers();
		}

        void removeInvalid() {
            EventMatcher<EventType>::removeInvalid();
            EventMatcher<OtherTypes...>::removeInvalid();
        }
	};



	template<typename EventType>
	class EventMatcher<EventType> {
		public:
        EventMatcher() : events(std::list<EventType>()), subscribers(std::list<std::unique_ptr<EventSubscriber<EventType>>>()) {}

		void logEvent(EventType&& event) noexcept {
			this->events.push_back(std::forward<EventType>(event));
		}

		void logSubscriber(std::unique_ptr<EventSubscriber<EventType>> subscriber) noexcept {
			this->subscribers.push_back(std::move(subscriber));
		}

        void removeInvalid() {
            auto iSub = this->subscribers.begin();
            while (iSub != this->subscribers.end()) {
                if (!(*iSub)->isValid()) {
                    iSub = this->subscribers.erase(iSub);

                    continue;
                }

                iSub++;
            }
        }

		void runSubscribers() {
			if (this->events.empty() || this->subscribers.empty()) {
				return;
			}

			auto iSub = this->subscribers.begin();
			while (iSub != this->subscribers.end()) {
				bool subErased = false;
				auto iEv = this->events.begin();
				while (iEv != this->events.end()) {
                    if (!(*iSub)->isValid()) {
                        iSub = this->subscribers.erase(iSub);
                        subErased = true;

                        break;
                    }

					if ((*iSub)->handle(*iEv)) {
						iEv = this->events.erase(iEv);
					} else {
						iEv++;
                    }
				}

				if (!subErased) {
					iSub++;
				}
			}

			this->events.clear();
		}

		private:

		std::list<EventType> events;
		std::list<std::unique_ptr<EventSubscriber<EventType>>> subscribers;
	};

	class DynamicsChangeEvent;
	class KeyPressedEvent;
	class KeyReleasedEvent;
	class MouseMoveEvent;

	typedef EventMatcher<
		LeftClickEvent,
		KeyPressedEvent,
		KeyReleasedEvent,
		DynamicsChangeEvent,
        MouseMoveEvent
	> BartaEventLoggerInterface;
}