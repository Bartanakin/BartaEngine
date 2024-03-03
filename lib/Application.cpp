#include <pch.h>
#include <Application.h>
#include <Collisions/CollisionDetectionStrategyInterface.h>
#include <BartaObjectManager.h>
#include <Objects/Rigid/RigidObjectCollisionSubscriber.h>
#include <Events/Subscribers/DynamicsChangeSubscriber.h>

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
    collisionExecutor(
        {{std::move(collisionDetectionStrategy)}},
        timer
    ),
    objectLists({})
{
    this->postDynamicsEventLogger->logSubscriber(std::make_unique<Barta::DynamicsChangeSubscriber>());

    this->collisionEventsLogger.logSubscriber(std::unique_ptr<Barta::Subscribers::RigidObjectRigidObject>(
        new Barta::StaticCollisionResponseSubscriberType<Barta::RigidObject, Barta::RigidObject>(
            *this->postDynamicsEventLogger
        )
    ));
}

Barta::Application::~Application() {}

void Barta::Application::run(){
	this->graphicsBridge->createWindow( Vector2f( 700.f, 700.f ), this->windowName );
	while( this->isRunning() && this->graphicsBridge->logEvents( *(this->eventLogger) )){
		this->timer.restart();
		while( !timer.finished() ){
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
			this->eventLogger->runSubscribers();
			this->dynamicsUpdateStrategy->update(this->objectManager->getDynamicsList(), timer.getCurrentDeltaTime());

            this->postDynamicUpdate(); // inheritable

			this->timer.forward();
		}

        // Rendering
		this->graphicsBridge->drawObjects( this->objectManager->getList() );

        this->preGarbageCollect(); // inheritable

        // Removing from containers and deleting relevant objects
        this->objectLists.StaticObjectManager<Barta::RigidObject>::reduceDeleted();
		this->objectManager->reduceDeleted();
	}
}

void Barta::Application::postDynamicUpdate() {
    this->postDynamicsEventLogger->runSubscribers();
}

bool Barta::Application::isRunning() const {
    return true;
}
