//
// Created by barta on 02/03/2024.
//

#include <Objects/Rigid/RigidObject.h>

Barta::RigidObject::RigidObject(
    GraphicsData graphicsData,
    std::unique_ptr<HitboxInterface> hitbox,
    DynamicsDTO dynamicsDto
) :
    graphicsData(std::move(graphicsData)),
    hitbox(std::move(hitbox)),
    dynamicsDTO(dynamicsDto)
{}

std::unique_ptr<const Barta::HitboxInterface> Barta::RigidObject::getHitbox() const{
    return this->hitbox->getTransformedHitbox(*this->graphicsData.transformable);
}

void Barta::RigidObject::rotate(float angle, Barta::Vector2f axis) {
    this->graphicsData.transformable->rotate(angle, axis);
}

void Barta::RigidObject::move(const Barta::Vector2f& shift){
    this->graphicsData.transformable->move(shift);
}

Barta::DynamicsDTO& Barta::RigidObject::getDynamicsDTO() {
    return this->dynamicsDTO;
}

Barta::GraphicsDataAwareInterface::GraphicsDataList Barta::RigidObject::getGraphicsData() {
    return {&this->graphicsData};
}
