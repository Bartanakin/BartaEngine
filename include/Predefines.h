#pragma once
#include <pch.h>
#include <Objects/Rigid/RigidObjectInterface.h>
#include <Collisions/CollisionExecutors/CollisionTestExecutor.h>
#include <Collisions/CollisionExecutors/FilterNoCollisionDecorator.h>
#include <Collisions/CollisionLogger.h>
#include <Events/BartaEventLoggerInterface.h>
#include <ReduceableList.h>
#include <StaticObjectManager.h>

namespace Barta {
    typedef ReducibleList<std::vector<RigidObjectInterface*>> RigidObjectContainer;

    typedef FilterNoCollisionDecorator<
        CollisionTestExecutor
    > CollisionCoreExecutor;

    typedef CollisionLogger<
        RigidObjectInterface, RigidObjectInterface
    > DefaultCollisionLogger; // <--

    typedef EventMatcher<
        CollisionEvent<RigidObjectInterface, RigidObjectInterface>
    > CollisionEventsLogger; // <--

    typedef StaticObjectManager<
        RigidObjectInterface
    > ListManager; // <--
}