#include <pch.h>
#include <Application.h>
#include <Collisions/CollisionDetectionStrategyInterface.h>

Barta::Application::Application(
    std::string windowName,
	std::unique_ptr<BartaGraphicsBridgeInterface> graphicsBridge,
	std::unique_ptr<BartaEventLoggerInterface> eventLogger,
	std::unique_ptr<BartaEventLoggerInterface> postDynamicsEventLogger,
	std::unique_ptr<ObjectManagerInterface> objectManager,
	std::unique_ptr<TimerInterface> timer,
	std::unique_ptr<DynamicsUpdateStrategyInterface> dynamicsUpdateStrategy
):
    windowName(std::move(windowName)),
	graphicsBridge(std::move(graphicsBridge)),
	eventLogger(std::move(eventLogger)),
	postDynamicsEventLogger(std::move(postDynamicsEventLogger)),
	objectManager(std::move(objectManager)),
	timer(std::move(timer)),
	dynamicsUpdateStrategy(std::move(dynamicsUpdateStrategy)) {
}

Barta::Application::~Application() {}

void Barta::Application::run(){
	this->graphicsBridge->createWindow( Vector2f( 700.f, 700.f ), this->windowName );
	while( this->isRunning() && this->graphicsBridge->logEvents( *(this->eventLogger) )){
		this->timer->restart();
		while( !timer->finished() ){
			this->checkLogic();

			this->eventLogger->runSubscribers();
			this->dynamicsUpdateStrategy->update(this->objectManager->getDynamicsList(), timer->getCurrentDeltaTime());

            this->postDynamicUpdate();

			this->timer->forward();
		}

		this->graphicsBridge->drawObjects( this->objectManager->getList() );

        this->preGarbageCollect();
		this->objectManager->reduceDeleted();
	}
}

void Barta::Application::postDynamicUpdate() {
    this->postDynamicsEventLogger->runSubscribers();
}

bool Barta::Application::isRunning() const {
    return true;
}
