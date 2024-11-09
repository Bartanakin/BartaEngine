//
// Created by barta on 02/03/2024.
//

#include <Objects/Rigid/RigidObject.h>

Barta::RigidObject::RigidObject(
    GraphicsData graphicsData,
    std::unique_ptr<HitboxInterface> hitbox,
    DynamicsDTO dynamicsDto
):
    graphicsData(std::move(graphicsData)),
    hitbox(std::move(hitbox)),
    dynamicsDTOCollection(dynamicsDto) {}

std::unique_ptr<const Barta::HitboxInterface> Barta::RigidObject::getHitbox() const {
    return this->hitbox->getTransformedHitbox(*this->graphicsData.transformable);
}

void Barta::RigidObject::rotate(
    float angle
) {
    this->rotate(angle, this->dynamicsDTOCollection[DynamicsDTOIteration::CURRENT].massCenter);
}

// TODO move rotation to update strategy
float Barta::RigidObject::getRotation() const {
    return this->graphicsData.transformable->getRotaion();
}

void Barta::RigidObject::setRotation(
    float angle
) {
    this->rotate(angle - this->graphicsData.transformable->getRotaion(), this->dynamicsDTOCollection[DynamicsDTOIteration::CURRENT].massCenter);
}

void Barta::RigidObject::rotate(
    float angle,
    Vector2f axis
) {
    this->graphicsData.transformable->rotate(angle, axis);
}

void Barta::RigidObject::move(
    const Vector2f& shift
) {
    this->graphicsData.transformable->move(shift);
    this->dynamicsDTOCollection[DynamicsDTOIteration::CURRENT].massCenter += shift;
}

Barta::DynamicsDTOCollection& Barta::RigidObject::getDynamicsDTOs() {
    return this->dynamicsDTOCollection;
}

Barta::GraphicsDataAwareInterface::GraphicsDataList Barta::RigidObject::getGraphicsData() {
    return {&this->graphicsData};
}
