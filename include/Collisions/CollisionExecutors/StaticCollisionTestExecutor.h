#pragma once

#include "../../pch.h"
#include "../../ReduceableList.h"
#include "../StaticCollisionAware.h"
#include "../CollcionTestResult/SExtendedCollisionResult.h"

namespace Barta {
    template<StaticCollisionAware T1, StaticCollisionAware T2>
    using ResultList = std::list<SExtendedCollisionResult<T1, T2>>;

    template<typename T>
    using ObjectList = std::vector<T>;

    template<typename Interface, typename T1, typename T2>
    concept StaticCollisionTestExecutorConcept = requires(Interface interface, ReducibleList<ObjectList<T1*>> t1, ReducibleList<ObjectList<T2*>> t2) {
        { interface.template executeTests<T1, T2>(t1, t2) } -> std::same_as<ResultList<T1, T2>>;
    };

	class StaticCollisionTestExecutor {
		public:
		StaticCollisionTestExecutor(std::unique_ptr<CollisionDetectionStrategyInterface> collisionDetectionStrategy) noexcept:
            collisionDetectionStrategy(std::move(collisionDetectionStrategy)) {
        }
        StaticCollisionTestExecutor(StaticCollisionTestExecutor&& second) = default;

		virtual ~StaticCollisionTestExecutor() noexcept = default;

        template<StaticCollisionAware T1, StaticCollisionAware T2> 
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

        template<StaticCollisionAware T> 
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
                            (*i)->getDynamicsDTO() - (*j)->getDynamicsDTO()
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

    template<StaticCollisionTestExecutorConcept<StaticCollisionAwareStub, StaticCollisionAwareStub> Decorated>
    class FilterNoCollisionDecorator {
		public:
		FilterNoCollisionDecorator(Decorated&& decorated) noexcept : decorated(std::forward<Decorated>(decorated)) {}
        FilterNoCollisionDecorator(FilterNoCollisionDecorator&& second) = default;
		~FilterNoCollisionDecorator() noexcept = default;

        template<StaticCollisionAware T1, StaticCollisionAware T2> 
		ResultList<T1, T2> executeTests(ReducibleList<ObjectList<T1*>>& list1, ReducibleList<ObjectList<T2*>>& list2) {
            return this->filterList<T1, T2>(this->decorated.template executeTests<T1, T2>(list1, list2));
        }

        template<StaticCollisionAware T> 
		ResultList<T, T> executeTestsForSame(ReducibleList<ObjectList<T*>>& list) {
            return this->filterList<T, T>(this->decorated.template executeTestsForSame<T>(list));
        }

		private:

        template<StaticCollisionAware T1, StaticCollisionAware T2>
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

    template<StaticCollisionTestExecutorConcept<StaticCollisionAwareStub, StaticCollisionAwareStub> Decorated>
    class SFilterCollisionsOvertimeDecorator {
		public:
		SFilterCollisionsOvertimeDecorator(
            Decorated&& decorated,
	        TimerInterface& timer
        ) noexcept :
            decorated(std::forward<Decorated>(decorated)),
            timer(timer)
        {}
		~SFilterCollisionsOvertimeDecorator() noexcept = default;

        template<StaticCollisionAware T1, StaticCollisionAware T2> 
		ResultList<T1, T2> executeTests(ReducibleList<ObjectList<T1*>>& list1, ReducibleList<ObjectList<T2*>>& list2) {
            return this->filterList<T1, T2>(this->decorated.template executeTests<T1, T2>(list1, list2));
        }

        template<StaticCollisionAware T> 
		ResultList<T, T> executeTestsForSame(ReducibleList<ObjectList<T*>>& list) {
            return this->filterList<T, T>(this->decorated.template executeTestsForSame<T>(list));
        }

#define COLLISION_EPS 0.00001f
		private:
        template<StaticCollisionAware T1, StaticCollisionAware T2>
        ResultList<T1, T2> filterList(ResultList<T1, T2> resultsList) {
            static SExtendedCollisionResult<T1, T2> lastCollisionResult = {};
            if (resultsList.empty()) {
                return resultsList;
            }

            float max_time = this->timer.getCurrentDeltaTime();
            auto i = resultsList.cbegin();
            while (i != resultsList.cend()) {
                if (i->object1->getDynamicsDTO().hasInfiniteMass
                    && i->object2->getDynamicsDTO().hasInfiniteMass) {
                    i++;

                    continue;
                }

                if ((*i) == lastCollisionResult) {
                    i = resultsList.erase(i);

                    continue;
                }

                if (
                    i->collisionTestResult.timePassed < max_time
                    && !i->collisionTestResult.staticCollision
                ) {
                    max_time = i->collisionTestResult.timePassed;
                }

                i++;
            }

            i = resultsList.cbegin();
            while (i != resultsList.cend()) {
                if (i->collisionTestResult.timePassed > max_time + COLLISION_EPS) {
                    i = resultsList.erase(i);

                    continue;
                }

                if (!i->collisionTestResult.staticCollision)
                    lastCollisionResult = *i;

                i++;
            }

            return resultsList;
        }

		Decorated decorated;
		TimerInterface& timer;
		constexpr const static float collisionTestError = 0.0001f;
	};

}