#pragma once
#include <Events/TemplateEventSubscriber.h>
#include <Geometrics/Point.h>
#include <pch.h>

namespace Barta {

class LeftClickEvent {
public:
    LeftClickEvent(
        Point position
    ) noexcept:
        position(position) {}

    Point getPosition() const noexcept { return this->position; }

private:
    Point position;
};

template<>
class EventSubscriber<LeftClickEvent> {
public:
    virtual ~EventSubscriber() noexcept = default;

    virtual bool handle(LeftClickEvent& event) = 0;

    virtual bool isToBeDeleted() const noexcept = 0;
};

typedef EventSubscriber<LeftClickEvent> LeftClickEventSubscriberInterface;
}
