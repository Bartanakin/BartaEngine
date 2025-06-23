#pragma once

#include <Events/Events/CollisionEvent.h>
#include <Events/TemplateEventSubscriber.h>
#include <Objects/Rigid/RigidObject.h>

namespace Barta::Events {

using RigidObjectRigidObject = CollisionEvent<RigidObjectInterface, RigidObjectInterface>;
}

SUBSCRIBER_INTERFACE_DEFINITION(Barta::Events::RigidObjectRigidObject);

namespace Barta::Subscribers {

using RigidObjectRigidObject = EventSubscriber<Events::RigidObjectRigidObject>;
}
