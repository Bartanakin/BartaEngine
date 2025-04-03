#pragma once
#include <Events/Events/CameraTransformationEvent.h>
#include <Graphics/BartaGraphicsBridgeInterface.h>
#include <pch.h>

namespace Barta::Events::Subscribers {
class CameraTransformationSubscriber: public Events::CameraTransformationSubscriberInterface {
public:
    CameraTransformationSubscriber(BartaGraphicsBridgeInterface& graphicsBridge) noexcept;

    bool handle(Barta::Events::Events::CameraTransformationEvent& event) override;

    bool isToBeDeleted() const noexcept override;

private:
    BartaGraphicsBridgeInterface& graphicsBridge;
};
}
