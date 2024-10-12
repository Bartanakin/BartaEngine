#include <Application.h>
#include <BartaObjectManager.h>
#include <Collisions/CollisionDetectionStrategyInterface.h>
#include <Events/Subscribers/DynamicsChangeSubscriber.h>
#include <Objects/Rigid/RigidObjectCollisionSubscriber.h>
#include <pch.h>

Barta::Application::Application(
    std::string windowName,
    std::unique_ptr<BartaGraphicsBridgeInterface> graphicsBridge,
    TimerInterface& timer,
    std::unique_ptr<DynamicsUpdateStrategyInterface> dynamicsUpdateStrategy,
    std::unique_ptr<CollisionDetectionStrategyInterface> collisionDetectionStrategy
):
    windowName(std::move(windowName)),
    graphicsBridge(std::move(graphicsBridge)),
    eventLogger(std::make_unique<BartaEventLoggerInterface>()),
    postDynamicsEventLogger(std::make_unique<BartaEventLoggerInterface>()),
    objectManager(std::unique_ptr<ObjectManagerInterface>(new BartaObjectManager())),
    timer(timer),
    dynamicsUpdateStrategy(std::move(dynamicsUpdateStrategy)),
    collisionEventsLogger({}),
    collisionExecutor(CollisionCoreExecutor(std::move(collisionDetectionStrategy))),
    objectLists({}) {
    this->postDynamicsEventLogger->logSubscriber(std::make_unique<DynamicsChangeSubscriber>());

    this->collisionEventsLogger.logSubscriber(std::unique_ptr<Subscribers::RigidObjectRigidObject>(
        new Barta::StaticCollisionResponseSubscriberType<RigidObjectInterface, RigidObjectInterface>(*this->postDynamicsEventLogger)
    ));
}

Barta::Application::~Application() {}

void Barta::Application::run() {
    this->graphicsBridge->createWindow(Vector2f(700.f, 700.f), this->windowName);
    while (this->isRunning() && this->graphicsBridge->logEvents(*(this->eventLogger))) {
        this->timer.restart();
        while (!timer.finished()) {
            this->checkLogic(); // inheritable

            // Collisions
            Barta::executeAndLog<DefaultCollisionLogger, CollisionEventsLogger, ListManager, CollisionCoreExecutor>(
                this->collisionEventsLogger,
                this->objectLists,
                this->collisionExecutor,
                this->timer
            );
            this->collisionEventsLogger.runSubscribers();

            // In-build events
            this->eventLogger->runSubscribersRecurrently();
            this->dynamicsUpdateStrategy->update(this->objectManager->getDynamicsList(), timer.getCurrentDeltaTime());

            this->postDynamicUpdate(); // inheritable

            this->timer.forward();
        }

        // Rendering
        this->graphicsBridge->drawObjects(this->objectManager->getGraphicsList());

        this->preGarbageCollect(); // inheritable

        // Removing from containers and deleting relevant objects
        this->objectLists.StaticObjectManager<Barta::RigidObjectInterface>::reduceDeleted();
        this->objectManager->reduceDeleted();
    }
}

void Barta::Application::postDynamicUpdate() {
    this->postDynamicsEventLogger->runSubscribers();
}

bool Barta::Application::isRunning() const {
    return true;
}
