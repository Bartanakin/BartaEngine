//
// Created by barta on 02/03/2024.
//

#include <Objects/Rigid/RigidObject.h>


Barta::RigidObject::RigidObject(
    std::unique_ptr<TransformableInterface> transformable,
    std::unique_ptr<HitboxInterface> hitbox,
    DynamicsDTO dynamicsDto
) :
    transformable(std::move(transformable)),
    hitbox(std::move(hitbox)),
    dynamicsDTO(dynamicsDto),
    resource({0})
{}

const Barta::TransformableInterface& Barta::RigidObject::getTransformable() const{
    return *this->transformable;
}

const Barta::BartaSprite* Barta::RigidObject::getResource() noexcept{
    return &this->resource;
}

std::unique_ptr<const Barta::HitboxInterface> Barta::RigidObject::getHitbox() const{
    return this->hitbox->getTransformedHitbox(*this->transformable);
}

void Barta::RigidObject::move(const Barta::Vector2f& shift){
    this->transformable->move(shift);
}

Barta::RigidObject* Barta::RigidObject::setVelocity(const Barta::Vector2f &velocity) {
    this->dynamicsDTO.velocity = velocity;

    return this;
}

const Barta::DynamicsDTO& Barta::RigidObject::getDynamicsDTO() const{
    return this->dynamicsDTO;
}

void Barta::RigidObject::setDynamicsDTO(const Barta::DynamicsDTO& dynamicsDTO){
    this->dynamicsDTO = dynamicsDTO;
}

int Barta::RigidObject::getZIndex() const {
    return 1;
}

void Barta::RigidObject::setResource(Barta::BartaSprite resource) {
    this->resource = resource;
}