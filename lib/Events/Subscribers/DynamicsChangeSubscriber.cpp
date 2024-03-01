#include <pch.h>
#include <Events/Subscribers/DynamicsChangeSubscriber.h>


bool Barta::DynamicsChangeSubscriber::handle(DynamicsChangeEvent& event) {
    event.dynamicsAware->setDynamicsDTO(event.dynamicsAware->getDynamicsDTO() + event.dynamicsDiff);

    return true;
}

bool Barta::DynamicsChangeSubscriber::isValid() const noexcept {
    return true;
}
