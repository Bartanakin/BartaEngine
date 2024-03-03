#include <Collisions/CollisionLogger.h>
#include "Sandbox.h"
#include "Dynamics/ConstVelocityDynamicsUpdateStrategy.h"
#include "Collisions/CollisionDetectionStrategies/DynamicCollisionDetectionStrategy.h"
#include "Geometrics/Math/BartaMathLibrary.h"
#include "Graphics/SFML_GraphicsBridge.h"
#include <Objects/Rigid/RigidObjectRepository.h>
#include <Dynamics/Timers/FrameLimitTimerProxy.h>
#include <Dynamics/Timers/SFML_Timer.h>

std::unique_ptr<Barta::TimerInterface> Sandbox::gameTimer = std::make_unique<Barta::FrameLimitTimerProxy>(
    std::make_unique<Barta::SFML_Timer>(),
    0.0f
);

Sandbox::Sandbox()
	: Application(
        "Sandbox",
		std::make_unique<Barta::SFML_GraphicsBridge>(),
        *Sandbox::gameTimer,
		std::make_unique<Barta::ConstVelocityDynamicsUpdateStrategy>(),
		std::make_unique<Barta::DynamicCollisionDetectionStrategy>(
            std::make_unique<Barta::BartaMathLibrary>(),
            *Sandbox::gameTimer
        )
	)
{
    auto repository = Barta::RigidObjectRepository(
        this->objectLists,
        *this->objectManager
    );

    auto ball1 = repository.addNewCircle(40.f, {255, 0, 255, 255});
    ball1->move({150.f, 150.f});
    ball1->setVelocity({45.f, 45.f});

    auto ball2 = repository.addNewCircle(40.f, {255, 255, 0, 255});
    ball2->move({310.f, 500.f});
    ball2->setVelocity({0.f, -60.f});

    auto ball3 = repository.addNewCircle(40.f, {0, 255, 255, 255});
    ball3->move({370.f, 150.f});
    ball3->setVelocity({0.f, 60.f});

    auto block1 = repository.addNewAABB({80.f, 80.f}, {255, 0, 0, 255});
    block1->move({310.f, 310.f});

    auto boundColor = Barta::Color(50, 191, 66, 255);
    auto leftBound = repository.addNewAABB({50.f, 650.f}, boundColor);
    leftBound->move({0.f, 0.f});
    auto topBound = repository.addNewAABB({650.f, 50.f}, boundColor);
    topBound->move({50.f, 0.f});
    auto rightBound = repository.addNewAABB({50.f, 650.f}, boundColor);
    rightBound->move({650.f, 50.f});
    auto bottomBound = repository.addNewAABB({650.f, 50.f}, boundColor);
    bottomBound->move({0.f, 650.f});
}

Sandbox::~Sandbox() {}
