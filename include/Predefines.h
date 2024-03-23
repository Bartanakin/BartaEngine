#pragma once
#include <pch.h>
#include <Objects/Rigid/RigidObject.h>
#include <Collisions/CollisionExecutors/CollisionTestExecutor.h>
#include <Collisions/CollisionExecutors/FilterNoCollisionDecorator.h>
#include <Collisions/CollisionLogger.h>
#include <Events/BartaEventLoggerInterface.h>
#include <ReduceableList.h>
#include <StaticObjectManager.h>

namespace Barta {
    typedef ReducibleList<std::vector<RigidObject*>> RigidObjectContainer;

    typedef FilterNoCollisionDecorator<
        CollisionTestExecutor
    > CollisionCoreExecutor;

    typedef CollisionLogger<
        RigidObject, RigidObject
    > DefaultCollisionLogger; // <--

    typedef EventMatcher<
        CollisionEvent<RigidObject, RigidObject>
    > CollisionEventsLogger; // <--

    typedef StaticObjectManager<
        RigidObject
    > ListManager; // <--
}