#include <pch.h>
#include <Events/Subscribers/DynamicsChangeSubscriber.h>


bool Barta::DynamicsChangeSubscriber::handle(DynamicsChangeEvent& event) {
    auto& dynamics = event.dynamicsAware->getDynamicsDTO();

    dynamics.velocity += event.velocityChange;

    return true;
}

bool Barta::DynamicsChangeSubscriber::isValid() const noexcept {
    return true;
}
