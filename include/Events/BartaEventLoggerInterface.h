#pragma once
#include "../pch.h"
#include "Events/Events/MouseMoveEvent.h"
#include "Events/KeyPressedEvent.h"
#include "Events/KeyReleasedEvent.h"
#include "Events/LeftClickEvent.h"
#include "Events/VelocityChangeEvent.h"

namespace Barta {
template<typename EventType, typename... OtherTypes>
class EventMatcher: public EventMatcher<EventType>, public EventMatcher<OtherTypes...> {
public:
    EventMatcher():
        EventMatcher<EventType>(),
        EventMatcher<OtherTypes...>() {}

    using EventMatcher<EventType>::logEvent;
    using EventMatcher<OtherTypes...>::logEvent;
    using EventMatcher<EventType>::logSubscriber;
    using EventMatcher<OtherTypes...>::logSubscriber;
    using EventMatcher<EventType>::countEvents;
    using EventMatcher<OtherTypes...>::countEvents;

    void runSubscribers() {
        EventMatcher<EventType>::runSubscribers();
        EventMatcher<OtherTypes...>::runSubscribers();
    }

    void removeInvalid() {
        EventMatcher<EventType>::removeInvalid();
        EventMatcher<OtherTypes...>::removeInvalid();
    }

    unsigned int countEvents() { return EventMatcher<EventType>::countEvents() + EventMatcher<OtherTypes...>::countEvents(); }

    void runSubscribersRecurrently() {
        int debugCounter = 0;
        while (this->countEvents() != 0) {
            this->runSubscribers();

            debugCounter++;
            if (debugCounter > 1000) {
                throw std::runtime_error("Subscribers have been run too many times!");
            }
        }
    }
};

template<typename EventType>
class EventMatcher<EventType> {
public:
    EventMatcher():
        events(std::list<EventType>()),
        subscribers(std::list<std::shared_ptr<EventSubscriber<EventType>>>()) {}

    void logEvent(
        EventType&& event
    ) noexcept {
        this->events.push_back(std::forward<EventType>(event));
    }

    void logSubscriber(
        std::shared_ptr<EventSubscriber<EventType>> subscriber
    ) noexcept {
        this->subscribers.push_back(std::move(subscriber));
    }

    unsigned int countEvents() { return this->events.size(); }

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
        if (this->events.empty()) {
            return;
        }

        if (this->subscribers.empty()) {
            this->events.clear();

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

    void runSubscribersRecurrently() {
        int debugCounter = 0;
        while (this->countEvents() != 0) {
            this->runSubscribers();

            debugCounter++;
            if (debugCounter > 1000) {
                throw std::runtime_error("Subscribers have been run too many times!");
            }
        }
    }

private:
    std::list<EventType> events;
    std::list<std::shared_ptr<EventSubscriber<EventType>>> subscribers;
};

class DynamicsChangeEvent;
class KeyPressedEvent;
class KeyReleasedEvent;
class MouseMoveEvent;

typedef EventMatcher<LeftClickEvent, KeyPressedEvent, KeyReleasedEvent, DynamicsChangeEvent, MouseMoveEvent> BartaEventLoggerInterface;
}
