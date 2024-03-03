#pragma once
#include "pch.h"
#include "Geometrics/Vector2f.h"
#include "Graphics/BartaGraphicsBridgeInterface.h"
#include "Events/BartaEventLoggerInterface.h"
#include"ObjectManagerInterface.h"
#include "Dynamics/TimerInterface.h"
#include "Dynamics/DynamicsUpdateStrategyInterface.h"
#include "Collisions/CollisionDetectionStrategyInterface.h"
#include <Predefines.h>

namespace Barta{
	class Application{
	public:
		Application(
            std::string windowName,
			std::unique_ptr<BartaGraphicsBridgeInterface> graphicsBridge,
			TimerInterface& timer,
			std::unique_ptr<DynamicsUpdateStrategyInterface> dynamicsUpdateStrategy,
            std::unique_ptr<Barta::CollisionDetectionStrategyInterface> collisionDetectionStrategy
		);
        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(const Application&) = delete;

		virtual ~Application();

		virtual void run() final;

		virtual void checkLogic() {};

        virtual void preGarbageCollect() {};

        virtual void postDynamicUpdate();

        virtual bool isRunning() const;

	protected:
        std::string windowName;
		std::unique_ptr<BartaGraphicsBridgeInterface> graphicsBridge;
		std::unique_ptr<BartaEventLoggerInterface> eventLogger;
		std::unique_ptr<BartaEventLoggerInterface> postDynamicsEventLogger;
		std::unique_ptr<ObjectManagerInterface> objectManager;
        TimerInterface& timer;
		std::unique_ptr<DynamicsUpdateStrategyInterface> dynamicsUpdateStrategy;
        CollisionEventsLogger collisionEventsLogger;
        CollisionCoreExecutor collisionExecutor;
        ListManager objectLists;
    };


}


