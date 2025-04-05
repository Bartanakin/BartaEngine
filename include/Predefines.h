#pragma once
#include "Dynamics/UpdateStrategy/ExplicitEulerStrategy.h"
#include "Dynamics/UpdateStrategy/SoftBodyStrategy.h"
#include "Objects/Soft/SoftObject.h"
#include <Collisions/CollisionExecutors/CollisionTestExecutor.h>
#include <Collisions/CollisionExecutors/FilterNoCollisionDecorator.h>
#include <Collisions/CollisionLogger.h>
#include <Dynamics/UpdateStrategy/UpdateStrategyManager.h>
#include <Events/BartaEventLoggerInterface.h>
#include <Objects/Rigid/RigidObjectCollisionSubscriber.h>
#include <Objects/Rigid/RigidObjectInterface.h>
#include <ReduceableList.h>
#include <StaticObjectManager.h>
#include <pch.h>

namespace Barta {

// clang-format off
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

typedef Dynamics::UpdateStrategy::UpdateStrategyManager<
    Dynamics::UpdateStrategy::ExplicitEulerStrategy, RigidObjectInterface,
    Dynamics::UpdateStrategy::SoftBodyStrategy, Objects::Soft::SoftObject
> PredefinedUpdateStrategyManager;
}
