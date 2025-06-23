#include <Objects/Rigid/RigidObject.h>
#include "Utilities/DynamicsIteration.h"

namespace Barta {
RigidObject::RigidObject(
    GraphicsData graphicsData,
    std::unique_ptr<HitboxInterface> hitbox,
    DynamicsDTO dynamicsDto
):
    graphicsData(std::move(graphicsData)),
    hitbox(std::move(hitbox)),
    dynamicsDTOCollection(dynamicsDto) {}

std::unique_ptr<const HitboxInterface> RigidObject::getHitbox() const {
    return this->hitbox->getTransformedHitbox(this->dynamicsDTOCollection[DynamicsDTOIteration::NEXT].getTransformation());
}

void RigidObject::move(
    const Vector& shift
) {
    Utils::extractCurrentDynamics(*this).massCenter += shift;
}

DynamicsDTOCollection& RigidObject::getDynamicsDTOs() {
    return this->dynamicsDTOCollection;
}

void RigidObject::rotate(
    const Quaternion& rotation
) {
    Utils::extractCurrentDynamics(*this).rotation *= rotation;
}

Vector RigidObject::getForce(
    DynamicsDTOIteration positionIteration,
    DynamicsDTOIteration velocityIteration
) {
    return Vector::Zero();
}

GraphicsDataAwareInterface::GraphicsDataList RigidObject::getGraphicsData() {
    this->graphicsData.transformation = Transformation::translation(Utils::extractCurrentDynamics(*this).massCenter.toVector())
                                        * Transformation::rotation(Utils::extractCurrentDynamics(*this).rotation) * Transformation::Identity();

    return {&this->graphicsData};
}
}
