#include <Objects/Rigid/RigidObject.h>

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
    return this->hitbox->getTransformedHitbox(this->graphicsData.transformation);
}

void RigidObject::move(
    const Vector& shift
) {
    DynamicsAwareInterface::getCurrentDynamics(*this).massCenter += shift;
}

DynamicsDTOCollection& RigidObject::getDynamicsDTOs() {
    return this->dynamicsDTOCollection;
}

void RigidObject::rotate(
    const Quaternion& rotation
) {
    DynamicsAwareInterface::getCurrentDynamics(*this).rotation *= rotation;
}

GraphicsDataAwareInterface::GraphicsDataList RigidObject::getGraphicsData() {
    this->graphicsData.transformation = Transformation::translation(DynamicsAwareInterface::getCurrentDynamics(*this).massCenter.toVector())
                                        * Transformation::rotation(DynamicsAwareInterface::getCurrentDynamics(*this).rotation)
                                        * Transformation::Identity();

    return {&this->graphicsData};
}
}
