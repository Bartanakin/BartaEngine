#pragma once

#include "Events/PositionAwareConcept.h"
#include "Events/TemplateEventSubscriber.h"
#include "Hitbox/HitboxAwareInterface.h"
namespace Barta {


template<PositionAware EventType>
class HitboxPositionCheckSubscriberProxy : public EventSubscriber<EventType> {
public:
    HitboxPositionCheckSubscriberProxy(
        HitboxAware* hitboxAware,
        std::unique_ptr<EventSubscriber<EventType>> delegate,
        bool outOfHitboxMode = false
    )
        : hitboxAware(hitboxAware),
          delegate(std::move(delegate)),
          outOfHitboxMode(outOfHitboxMode)
    {}
    HitboxPositionCheckSubscriberProxy(const HitboxPositionCheckSubscriberProxy &) = delete;
    HitboxPositionCheckSubscriberProxy(HitboxPositionCheckSubscriberProxy &&) = default;
    HitboxPositionCheckSubscriberProxy & operator=(const HitboxPositionCheckSubscriberProxy &) = delete;
    HitboxPositionCheckSubscriberProxy & operator=(
        HitboxPositionCheckSubscriberProxy &&) = default;

    virtual bool handle(EventType& event) override {
        if (this->hitboxAware->getHitbox()->isWithin(event.getPosition()) != this->outOfHitboxMode) {
            return this->delegate->handle(event);
        }

        return false;
    }

    virtual bool isValid() const noexcept override {
        return this->delegate->isValid();
    }

private:

    HitboxAware* hitboxAware;
    std::unique_ptr<EventSubscriber<EventType>> delegate;
    const bool outOfHitboxMode;
};

} // namespace Barta
