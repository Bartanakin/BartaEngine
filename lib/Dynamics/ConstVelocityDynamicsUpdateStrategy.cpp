#include <pch.h>
#include <Dynamics/ConstVelocityDynamicsUpdateStrategy.h>

#define ZEROING_EDGE 0.5f

void Barta::ConstVelocityDynamicsUpdateStrategy::update(
	DynamicsAwareInterface::DynamicsAwareList& objectList, 
	const float deltaTime
) {
	for (auto object : objectList) {
        auto dynamics = object->getDynamicsDTO();
        if (dynamics.hasInfiniteMass) {
            continue;
        }

		object->move(dynamics.velocity * deltaTime + 0.5f * dynamics.acceleration * deltaTime * deltaTime);
		object->rotate(dynamics.rotationVelocity *deltaTime, dynamics.massCenter);

        dynamics.velocity = Vector2f::zeroise(dynamics.velocity + dynamics.acceleration * deltaTime, ZEROING_EDGE);

        object->setDynamicsDTO(std::move(dynamics));
	}
}
