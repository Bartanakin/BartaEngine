#pragma once
#include <Events/TemplateEventSubscriber.h>
#include <Geometrics/Point.h>
#include <pch.h>

namespace Barta::Events::Events {

struct CameraTransformationEvent {
    CameraTransformationEvent() noexcept = default;

    CameraTransformationEvent(
        Point eye,
        Point center,
        Vector up
    ) noexcept:
        eye(eye),
        center(center),
        up(up) {}

    Point eye;
    Point center;
    Vector up;
};
}

SUBSCRIBER_INTERFACE_DEFINITION(Barta::Events::Events::CameraTransformationEvent);

namespace Barta::Events::Events {
typedef EventSubscriber<CameraTransformationEvent> CameraTransformationSubscriberInterface;
}
