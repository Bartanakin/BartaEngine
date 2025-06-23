#pragma once

#include "Objects/Soft/SoftObject.h"
#include <Events/Events/CollisionEvent.h>
#include <Events/TemplateEventSubscriber.h>
#include <Objects/Rigid/RigidObject.h>

namespace Barta::Events {

using RigidObjectSoftObject = CollisionEvent<RigidObjectInterface, Objects::Soft::SoftObject>;
}

SUBSCRIBER_INTERFACE_DEFINITION(Barta::Events::RigidObjectSoftObject);

namespace Barta::Subscribers {

using RigidObjectSoftObject = EventSubscriber<Events::RigidObjectSoftObject>;
}
