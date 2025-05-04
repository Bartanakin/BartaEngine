#pragma once
#include "Collisions/CollisionDetectionStrategyInterface.h"
#include "Dynamics/TimerInterface.h"
#include "Graphics/BartaGraphicsBridgeInterface.h"
#include "pch.h"
#include <BartaObjectManager.h>
#include <Predefines.h>

namespace Barta {

template<typename CollisionLogger, typename EventLogger, typename ObjectManager, typename TestExecutor, typename UpdateStrategyManagerType>
    requires Dynamics::UpdateStrategy::
        UpdateStrategyManagerConcept<UpdateStrategyManagerType, ObjectManager, RigidObjectInterface> // TODO concepts for all typenames
    class Application {
public:
    Application(
        std::string windowName,
        std::unique_ptr<BartaGraphicsBridgeInterface> graphicsBridge,
        TimerInterface& timer,
        std::unique_ptr<Barta::CollisionDetectionStrategyInterface> collisionDetectionStrategy,
        UpdateStrategyManagerType updateStrategyManager
    ):
        windowName(std::move(windowName)),
        graphicsBridge(std::move(graphicsBridge)),
        eventLogger(std::make_unique<BartaEventLoggerInterface>()),
        objectManager(std::make_unique<BartaObjectManager>()),
        timer(timer),
        collisionEventsLogger({}),
        collisionExecutor(CollisionCoreExecutor(std::move(collisionDetectionStrategy))),
        objectLists({}),
        updateStrategyManager(std::move(updateStrategyManager)) {}

    Application(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(const Application&) = delete;
    virtual ~Application() = default;

    virtual void run() {
        this->graphicsBridge->createWindow(Vector2f(700.f, 700.f), this->windowName);
        this->timer.restart();
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        while (this->isRunning() && this->graphicsBridge->logEvents(*(this->eventLogger))) {
            this->timer.restart();
            while (!timer.finished()) {
                this->checkLogic(); // inheritable

                auto deltaBeforeCollisions = timer.getCurrentDeltaTime();
                this->updateStrategyManager.prepare(this->objectLists, timer.getCurrentDeltaTime());

                // Collisions
                Barta::executeAndLog<CollisionLogger, EventLogger, ObjectManager, TestExecutor>(
                    this->collisionEventsLogger,
                    this->objectLists,
                    this->collisionExecutor,
                    this->timer
                );

                if (deltaBeforeCollisions != timer.getCurrentDeltaTime()) {
                    this->updateStrategyManager.prepare(this->objectLists, timer.getCurrentDeltaTime());
                }

                this->collisionEventsLogger.runSubscribers();

                // In-build events
                this->eventLogger->runSubscribersRecurrently();

                this->postDynamicUpdate(); // inheritable

                this->updateStrategyManager.update(this->objectLists, true);

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

    virtual bool isRunning() { return true; }

protected:
    std::string windowName;
    std::unique_ptr<BartaGraphicsBridgeInterface> graphicsBridge;
    std::unique_ptr<BartaEventLoggerInterface> eventLogger;
    std::unique_ptr<ObjectManagerInterface> objectManager;
    TimerInterface& timer;
    EventLogger collisionEventsLogger;
    TestExecutor collisionExecutor;
    ObjectManager objectLists;
    UpdateStrategyManagerType updateStrategyManager;
};

}
