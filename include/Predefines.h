#pragma once
#include "Objects/Soft/SoftObject.h"
#include <Collisions/CollisionExecutors/CollisionTestExecutor.h>
#include <Collisions/CollisionExecutors/FilterNoCollisionDecorator.h>
#include <Collisions/CollisionLogger.h>
#include <Events/BartaEventLoggerInterface.h>
#include <Objects/Rigid/RigidObjectCollisionSubscriber.h>
#include <Objects/Rigid/RigidObjectInterface.h>
#include <ReduceableList.h>
#include <StaticObjectManager.h>
#include <pch.h>

namespace Barta {

typedef FilterNoCollisionDecorator<CollisionTestExecutor> CollisionCoreExecutor;

/**
 * Always insert types in pairs. Each pair tells the logger which object types should be searched for collision.
 * This class runs collision test executors and logs the collisions to an event matcher.
 */
typedef CollisionLogger<RigidObjectInterface, RigidObjectInterface> DefaultCollisionLogger;

/**
 * This class pairs the found collisions with respective subscribers.
 */
typedef EventMatcher<CollisionEvent<RigidObjectInterface, RigidObjectInterface>> CollisionEventsLogger; // <--

typedef StaticObjectManager<RigidObjectInterface, Objects::Soft::SoftObject> ListManager; // <--
}
