#include <Events/Subscribers/CameraTransformationSubscriber.h>

namespace Barta::Events::Subscribers {
CameraTransformationSubscriber::CameraTransformationSubscriber(
    BartaGraphicsBridgeInterface& graphicsBridge
) noexcept:
    graphicsBridge(graphicsBridge) {}

bool CameraTransformationSubscriber::handle(
    Barta::Events::Events::CameraTransformationEvent& event
) {
    this->graphicsBridge.getViewTransformation() = Transformation::lookAt(event.eye, event.center - event.eye, event.up) * Transformation::Identity();

    return true;
}

bool CameraTransformationSubscriber::isToBeDeleted() const noexcept {
    return false;
}
}
