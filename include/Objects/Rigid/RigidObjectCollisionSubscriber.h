#pragma once

#include <Events/TemplateEventSubscriber.h>
#include <Events/Events/CollisionEvent.h>
#include <Events/Subscribers/CollisionResponseSubscriber.h>
#include <Objects/Rigid/RigidObject.h>

namespace Barta {
    namespace Events {
        using RigidObjectRigidObject = Barta::CollisionEvent<RigidObjectInterface, RigidObjectInterface>;
    }
}

SUBSCRIBER_INTERFACE_DEFINITION(Barta::Events::RigidObjectRigidObject);

namespace Barta {
    namespace Subscribers {
        using RigidObjectRigidObject = Barta::EventSubscriber<Events::RigidObjectRigidObject>;
    };
}