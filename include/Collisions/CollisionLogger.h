#pragma once

#include "CollisionAware.h"
#include <Collisions/CollisionTestResult/ExtendedCollisionResult.h>
#include <Events/Events/CollisionEvent.h>
#include <Collisions/CollisionExecutors/CollisionTestExecutor.h>

namespace Barta {
    // TODO - refactor
    template<CollisionAware T1, CollisionAware T2>
    using ResultList = std::list<ExtendedCollisionResult<T1, T2>>;

    template<
            typename CollisionLogger,
            typename EventLogger,
            typename ObjectManager,
            typename TestExecutor
    >
    void executeAndLog(
            EventLogger& eventLogger,
            ObjectManager& objectManager,
            TestExecutor& testExecutor,
            TimerInterface& timer
    ) {
        auto staticCollisionLogger = CollisionLogger();
        float delta_time = staticCollisionLogger.execute(objectManager, testExecutor);

        if (timer.getCurrentDeltaTime() <= delta_time) {
            return;
        }

        timer.setCurrentDeltaTime(std::min(delta_time + COLLISION_EPS, timer.getCurrentDeltaTime()));
        staticCollisionLogger.logEvent(eventLogger, delta_time);
    }

    template<
        CollisionAware T1,
        CollisionAware T2,
        CollisionAware ... Ts
    >
    class CollisionLogger : protected CollisionLogger<T1, T2>, protected CollisionLogger<Ts...> {
        public:
        CollisionLogger() noexcept :
            CollisionLogger<T1, T2>(),
            CollisionLogger<Ts...>()
        {}

        template<typename ObjectManager, typename TestExecutor>
        float execute(ObjectManager& objectManager, TestExecutor& testExecutor) {
            auto t1 = CollisionLogger<T1, T2>::template execute<ObjectManager, TestExecutor>(objectManager, testExecutor);
            auto t2 = CollisionLogger<Ts...>::template execute<ObjectManager, TestExecutor>(objectManager, testExecutor);
        
            return std::min(t1, t2);
        }

        template<typename EventLogger>
        void logEvent(EventLogger& eventLogger, const float min_time) {
            CollisionLogger<T1, T2>::template logEvent<EventLogger>(eventLogger, min_time);
            CollisionLogger<Ts...>::template logEvent<EventLogger>(eventLogger, min_time);
        }
    };

    template<
        CollisionAware T1,
        CollisionAware T2
    >
    class CollisionLogger<T1, T2> {
        public:

        template<typename ObjectManager, typename TestExecutor>
        float execute(ObjectManager& objectManager, TestExecutor& testExecutor) {
            this->testResults = {};
            float delta_time = 1000.f; // TODO
            auto testResults = testExecutor.template executeTests<T1, T2>(
                objectManager.getList(static_cast<T1*>(nullptr)),
                objectManager.getList(static_cast<T2*>(nullptr))
            );

            for (const auto& testResult : testResults) {
                if (testResult.collisionTestResult.timePassed < delta_time && !testResult.collisionTestResult.staticCollision) {
                    delta_time = testResult.collisionTestResult.timePassed;
                }
			}

            for (const auto& testResult : testResults) {
                if (testResult.collisionTestResult.timePassed < delta_time + COLLISION_EPS && !testResult.collisionTestResult.staticCollision) {
                    this->testResults.push_back(testResult);
                }
            }

            this->my_time = delta_time;

            return delta_time;
        }

        template<typename EventLogger>
        void logEvent(EventLogger& eventLogger, const float min_time) {
            if (min_time >= this->my_time) {
                for (auto& testResult : this->testResults) {
                    eventLogger.template logEvent(CollisionEvent<T1, T2>(testResult, this->my_time));
                }
            }
        }

        private:
        std::vector<ExtendedCollisionResult<T1, T2>> testResults;
        float my_time = 1000.f;
    };

    template<CollisionAware T>
    class CollisionLogger<T, T> {
        public:

        template<typename ObjectManager, typename TestExecutor>
        float execute(ObjectManager& objectManager, TestExecutor& testExecutor) {
            float delta_time = 1000.f; // TODO
            auto testResults = testExecutor.template executeTestsForSame<T>(
                objectManager.getList(static_cast<T*>(nullptr))
            );

            for (const auto& testResult : testResults) {
                if (testResult.collisionTestResult.timePassed < delta_time && !testResult.collisionTestResult.staticCollision) {
                    delta_time = testResult.collisionTestResult.timePassed;
                    this->testResult = testResult;
                }
			}

            this->my_time = delta_time;

            return delta_time;
        }

        template<typename EventLogger>
        void logEvent(EventLogger& eventLogger, const float min_time) {
            if (min_time >= this->my_time) {
                eventLogger.logEvent(CollisionEvent<T, T>(this->testResult, this->my_time));
            }
        }

        private:
        ExtendedCollisionResult<T, T> testResult = {};
        float my_time = 1000.f;
    };
}