//
// Created by barta on 02/03/2024.
//

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

void RigidObject::rotate(
    float angle
) {
    this->rotate(angle, this->dynamicsDTOCollection[DynamicsDTOIteration::CURRENT].massCenter);
}

// TODO move rotation to update strategy
float RigidObject::getRotation() const {
    return this->graphicsData.transformation.getRotation(Vector::Z_Axis());
}

void RigidObject::rotate(
    float angle,
    const Point& origin
) {
    this->graphicsData.transformation = Transformation::rotation(angle, origin) * this->graphicsData.transformation;
}

void RigidObject::move(
    const Vector& shift
) {
    this->graphicsData.transformation = Transformation::translation(shift) * this->graphicsData.transformation;
    this->dynamicsDTOCollection[DynamicsDTOIteration::CURRENT].massCenter += shift;
}

DynamicsDTOCollection& RigidObject::getDynamicsDTOs() {
    return this->dynamicsDTOCollection;
}

GraphicsDataAwareInterface::GraphicsDataList RigidObject::getGraphicsData() {
    return {&this->graphicsData};
}
}
