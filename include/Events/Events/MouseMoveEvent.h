#pragma once
#include <Events/TemplateEventSubscriber.h>
#include <Geometrics/Point.h>
#include <pch.h>

namespace Barta {

class MouseMoveEvent {
public:
    MouseMoveEvent(
        Point position
    ) noexcept:
        position(position) {}

    Point getPosition() const noexcept { return this->position; }

private:
    Point position;
};
}

SUBSCRIBER_INTERFACE_DEFINITION(Barta::MouseMoveEvent);

namespace Barta {
typedef EventSubscriber<MouseMoveEvent> MouseMoveSubscriberInterface;
}
