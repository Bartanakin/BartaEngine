#pragma once

#include "../../pch.h"
#include "../../ReduceableList.h"
#include "../CollisionAware.h"
#include <Collisions/CollisionTestResult/ExtendedCollisionResult.h>
#include <Collisions/CollisionExecutors/CollisionTestExecutorConcept.h>

namespace Barta {
    template<CollisionTestExecutorConcept<CollisionAwareStub, CollisionAwareStub> Decorated>
    class FilterNoCollisionDecorator {
    public:
        FilterNoCollisionDecorator(Decorated&& decorated) noexcept : decorated(std::forward<Decorated>(decorated)) {}
        FilterNoCollisionDecorator(FilterNoCollisionDecorator&& second) = default;
        ~FilterNoCollisionDecorator() noexcept = default;

        template<CollisionAware T1, CollisionAware T2>
        ResultList<T1, T2> executeTests(ReducibleList<ObjectList<T1*>>& list1, ReducibleList<ObjectList<T2*>>& list2) {
            return this->filterList<T1, T2>(this->decorated.template executeTests<T1, T2>(list1, list2));
        }

        template<CollisionAware T>
        ResultList<T, T> executeTestsForSame(ReducibleList<ObjectList<T*>>& list) {
            return this->filterList<T, T>(this->decorated.template executeTestsForSame<T>(list));
        }

    private:

        template<CollisionAware T1, CollisionAware T2>
        ResultList<T1, T2> filterList(ResultList<T1, T2> resultsList) {
            auto i = resultsList.begin();
            while (i != resultsList.end()) {
                if (i->collisionTestResult.collisionDetected) {
                    i++;

                    continue;
                }

                i = resultsList.erase(i);
            }

            return resultsList;
        }

        Decorated decorated;
    };
}