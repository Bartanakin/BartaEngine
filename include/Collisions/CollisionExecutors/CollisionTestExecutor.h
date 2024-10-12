#pragma once

#include "../../pch.h"
#include "../../ReduceableList.h"
#include "../CollisionAware.h"
#include <Collisions/CollisionTestResult/ExtendedCollisionResult.h>
#include <Collisions/CollisionExecutors/CollisionTestExecutorConcept.h>

namespace Barta {
	class CollisionTestExecutor {
		public:
		CollisionTestExecutor(std::unique_ptr<CollisionDetectionStrategyInterface> collisionDetectionStrategy) noexcept:
            collisionDetectionStrategy(std::move(collisionDetectionStrategy)) {
        }
        CollisionTestExecutor(CollisionTestExecutor&& second) = default;

		virtual ~CollisionTestExecutor() noexcept = default;

        template<CollisionAware T1, CollisionAware T2>
		ResultList<T1, T2> executeTests(ReducibleList<ObjectList<T1*>>& list1, ReducibleList<ObjectList<T2*>>& list2) {
            ResultList<T1, T2>  collisionResults;

            auto i = list1.begin();
            while (i != list1.end()) {
                auto j = list2.begin();
                while (j != list2.end()) {
                    collisionResults.push_back({
                        (*i)->getHitbox()->intersects(
                            *((*j)->getHitbox()),
                            *(this->collisionDetectionStrategy),
                            (*i)->getDynamicsDTO() - (*j)->getDynamicsDTO()
                        )
                    , (*i), (*j)});
                        
                    j++;
                }

                i++;
            }

            return collisionResults;
        }

        template<CollisionAware T>
		ResultList<T, T> executeTestsForSame(ReducibleList<ObjectList<T*>>& list) {
            ResultList<T, T>  collisionResults;

            auto i = list.begin();
            auto j_beg = list.begin();
            while (i != list.end()) {
                j_beg++;
                auto j = j_beg;
                while (j != list.end()) {
                    collisionResults.push_back({
                        (*i)->getHitbox()->intersects(
                            *((*j)->getHitbox()),
                            *(this->collisionDetectionStrategy),
                            (*i)->getDynamicsDTO().getRelativeDynamics((*j)->getDynamicsDTO())
                        )
                    , (*i), (*j)});
                        
                    j++;
                }

                i++;
            }

            return collisionResults;
        }

		private:

		std::unique_ptr<CollisionDetectionStrategyInterface> collisionDetectionStrategy;
	};
}