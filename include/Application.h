#pragma once
#include <BartaObjectManager.h>

#include "Collisions/CollisionDetectionStrategyInterface.h"
#include "Dynamics/DynamicsUpdateStrategyInterface.h"
#include "Dynamics/TimerInterface.h"
#include "Graphics/BartaGraphicsBridgeInterface.h"
#include "pch.h"
#include <Predefines.h>

namespace Barta {

template<typename CollisionLogger, typename EventLogger, typename ObjectManager, typename TestExecutor>
class Application {
public:
    Application(
        std::string windowName,
        std::unique_ptr<BartaGraphicsBridgeInterface> graphicsBridge,
        TimerInterface& timer,
        std::unique_ptr<DynamicsUpdateStrategyInterface> dynamicsUpdateStrategy,
        std::unique_ptr<Barta::CollisionDetectionStrategyInterface> collisionDetectionStrategy
    ):
        windowName(std::move(windowName)),
        graphicsBridge(std::move(graphicsBridge)),
        eventLogger(std::make_unique<BartaEventLoggerInterface>()),
        objectManager(std::make_unique<BartaObjectManager>()),
        timer(timer),
        dynamicsUpdateStrategy(std::move(dynamicsUpdateStrategy)),
        collisionEventsLogger({}),
        collisionExecutor(CollisionCoreExecutor(std::move(collisionDetectionStrategy))),
        objectLists({}) {
        // this->collisionEventsLogger.logSubscriber(std::unique_ptr<Subscribers::RigidObjectRigidObject>(
        //     new Barta::StaticCollisionResponseSubscriberType<RigidObjectInterface, RigidObjectInterface>(*this->postDynamicsEventLogger)
        // ));
    }

    Application(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(const Application&) = delete;
    virtual ~Application() = default;

    virtual void run() {
        this->graphicsBridge->createWindow(Vector2f(700.f, 700.f), this->windowName);
        while (this->isRunning() && this->graphicsBridge->logEvents(*(this->eventLogger))) {
            this->timer.restart();
            while (!timer.finished()) {
                this->checkLogic(); // inheritable

                auto deltaBeforeCollisions = timer.getCurrentDeltaTime();
                this->dynamicsUpdateStrategy->prepare(timer.getCurrentDeltaTime());

                // Collisions
                Barta::executeAndLog<CollisionLogger, EventLogger, ObjectManager, TestExecutor>(
                    this->collisionEventsLogger,
                    this->objectLists,
                    this->collisionExecutor,
                    this->timer
                );

                if (deltaBeforeCollisions != timer.getCurrentDeltaTime()) {
                    this->dynamicsUpdateStrategy->prepare(timer.getCurrentDeltaTime());
                }

                this->collisionEventsLogger.runSubscribers();

                // In-build events
                this->eventLogger->runSubscribersRecurrently();

                this->postDynamicUpdate(); // inheritable

                this->dynamicsUpdateStrategy->update();

                this->timer.forward();
            }

            // Rendering
            this->graphicsBridge->drawObjects(this->objectManager->getGraphicsList());

            this->preGarbageCollect(); // inheritable

            // Removing from containers and deleting relevant objects
            // this->objectLists.template ObjectManager<Barta::RigidObjectInterface>::reduceDeleted();
            this->objectManager->reduceDeleted();
        }
    }

    virtual void checkLogic() {}

    virtual void preGarbageCollect() {}

    virtual void postDynamicUpdate() {}

    virtual bool isRunning() const { return true; }

protected:
    std::string windowName;
    std::unique_ptr<BartaGraphicsBridgeInterface> graphicsBridge;
    std::unique_ptr<BartaEventLoggerInterface> eventLogger;
    std::unique_ptr<ObjectManagerInterface> objectManager;
    TimerInterface& timer;
    std::unique_ptr<DynamicsUpdateStrategyInterface> dynamicsUpdateStrategy;
    EventLogger collisionEventsLogger;
    TestExecutor collisionExecutor;
    ObjectManager objectLists;
};

}
