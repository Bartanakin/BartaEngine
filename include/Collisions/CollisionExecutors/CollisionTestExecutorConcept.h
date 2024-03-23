#pragma once

#include "../../pch.h"
#include "../../ReduceableList.h"
#include "../CollisionAware.h"
#include <Collisions/CollisionTestResult/ExtendedCollisionResult.h>

namespace Barta {
#define COLLISION_EPS 0.00001f

    template<CollisionAware T1, CollisionAware T2>
    using ResultList = std::list<ExtendedCollisionResult<T1, T2>>;

    template<typename T>
    using ObjectList = std::vector<T>;

    template<typename Interface, typename T1, typename T2>
    concept CollisionTestExecutorConcept = requires(Interface interface, ReducibleList<ObjectList<T1*>> t1, ReducibleList<ObjectList<T2*>> t2) {
        { interface.template executeTests<T1, T2>(t1, t2) } -> std::same_as<ResultList<T1, T2>>;
    };
}