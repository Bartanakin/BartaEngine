//
// Created by barta on 02/03/2024.
//

#include <Objects/Rigid/RigidCompositeObject.h>
#include <Hitbox/NullHitbox.h>
#include "Hitbox/HitboxComposite.h"

Barta::RigidCompositeObject::RigidCompositeObject(
    std::unique_ptr<TransformableInterface> transformable,
    DynamicsDTO dynamicsDto,
    std::vector<RigidObjectInterface*> children
) :
    transformable(std::move(transformable)),
    dynamicsDto(dynamicsDto),
    children(std::move(children))
{}

bool Barta::RigidCompositeObject::isToBeDeleted() const {
    return false;
}

std::unique_ptr<const Barta::HitboxInterface> Barta::RigidCompositeObject::getHitbox() const{
    if (this->children.empty()) {
        return std::unique_ptr<const HitboxInterface>(new NullHitbox());
    }

    HitboxComposite::HitboxesList list = {};
    for (auto& child : this->children) {
        list.push_back(child->getHitbox());
    }

    return std::unique_ptr<const Barta::HitboxInterface>(new HitboxComposite(std::move(list)));
}

void Barta::RigidCompositeObject::rotate(float angle, Barta::Vector2f axis) {
    this->transformable->rotate(angle, axis);
    for (auto& child : this->children) {
        child->rotate(angle, axis);
    }
}

void Barta::RigidCompositeObject::move(const Barta::Vector2f& shift){
    this->transformable->move(shift);
    for (auto& child : this->children) {
        child->move(shift);
    }
}

Barta::DynamicsDTO& Barta::RigidCompositeObject::getDynamicsDTO() {
    return this->dynamicsDto;
}

Barta::GraphicsDataAwareInterface::GraphicsDataList Barta::RigidCompositeObject::getGraphicsData() {
    GraphicsDataList list = {};
    for (auto child : this->children) {
        auto childList = child->getGraphicsData();
        list.reserve(list.size() + childList.size());

        list.insert(list.end(), childList.begin(), childList.end());
    }

    return list;
}

void Barta::RigidCompositeObject::addNewChild(Barta::RigidObjectInterface* newChild) {
    this->children.push_back(newChild);
    newChild->getDynamicsDTO() = DynamicsDTO({});
}

Barta::RigidCompositeObject::~RigidCompositeObject() noexcept {
    for (auto child : this->children) {
        delete child;
    }
}
