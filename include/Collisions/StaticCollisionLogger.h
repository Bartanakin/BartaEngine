#pragma once

#include "StaticCollisionAware.h"
#include "CollcionTestResult/SExtendedCollisionResult.h"
#include "../Events/Events/SCollisionEvent.h"

namespace Barta {
    // TODO - refactor
    template<StaticCollisionAware T1, StaticCollisionAware T2>
    using ResultList = std::list<SExtendedCollisionResult<T1, T2>>;

    template<
        StaticCollisionAware T1,
        StaticCollisionAware T2,
        StaticCollisionAware ... Ts
    >
    class StaticCollisionLogger : protected StaticCollisionLogger<T1, T2>, protected StaticCollisionLogger<Ts...> {
        public:
        StaticCollisionLogger() noexcept :
            StaticCollisionLogger<T1, T2>(),
            StaticCollisionLogger<Ts...>()
        {}

        template<
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
            float delta_time = this->execute(objectManager, testExecutor);
            
            if (timer.getCurrentDeltaTime() <= delta_time) {
                return;
            }
            
            timer.setCurrentDeltaTime(std::min(delta_time + COLLISION_EPS, timer.getCurrentDeltaTime()));
            this->logEvent(eventLogger, delta_time);
        }

        protected:
        template<typename ObjectManager, typename TestExecutor>
        float execute(ObjectManager& objectManager, TestExecutor& testExecutor) {
            auto t1 = StaticCollisionLogger<T1, T2>::template execute<ObjectManager, TestExecutor>(objectManager, testExecutor);
            auto t2 = StaticCollisionLogger<Ts...>::template execute<ObjectManager, TestExecutor>(objectManager, testExecutor);
        
            return std::min(t1, t2);
        }

        template<typename EventLogger>
        void logEvent(EventLogger& eventLogger, const float min_time) {
            StaticCollisionLogger<T1, T2>::template logEvent<EventLogger>(eventLogger, min_time);
            StaticCollisionLogger<Ts...>::template logEvent<EventLogger>(eventLogger, min_time);
        }
    };

    template<
        StaticCollisionAware T1,
        StaticCollisionAware T2
    >
    class StaticCollisionLogger<T1, T2> {
        public:

        protected:
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
                    eventLogger.template logEvent(SCollisionEvent<T1, T2>(testResult, this->my_time));
                }
            }
        }

        private:
        std::vector<SExtendedCollisionResult<T1, T2>> testResults;
        float my_time = 1000.f;
    };

    template<StaticCollisionAware T>
    class StaticCollisionLogger<T, T> {
        public:

        protected:
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
                eventLogger.template logEvent(SCollisionEvent<T, T>(this->testResult, this->my_time));
            }
        }

        private:
        SExtendedCollisionResult<T, T> testResult = {};
        float my_time = 1000.f;
    };
}