//
// Created by barta on 02/03/2024.
//

#include <Objects/Rigid/RigidCompositeObject.h>
#include "Hitbox/HitboxComposite.h"
#include <Hitbox/NullHitbox.h>

Barta::RigidCompositeObject::RigidCompositeObject(
    Transformation transformation,
    DynamicsDTO dynamicsDto,
    std::vector<RigidObjectInterface*> children
):
    transformation(std::move(transformation)),
    dynamicsDtoCollection(dynamicsDto),
    children(std::move(children)) {}

bool Barta::RigidCompositeObject::isToBeDeleted() const {
    return false;
}

std::unique_ptr<const Barta::HitboxInterface> Barta::RigidCompositeObject::getHitbox() const {
    if (this->children.empty()) {
        return std::make_unique<const NullHitbox>();
    }

    HitboxComposite::HitboxesList list = {};
    for (auto& child: this->children) {
        list.push_back(child->getHitbox());
    }

    return std::make_unique<const HitboxComposite>(std::move(list));
}

void Barta::RigidCompositeObject::move(
    const Vector& shift
) {
    this->transformation = Transformation(Transformation::translation(shift) * this->transformation.getMatrix());
    for (auto& child: this->children) {
        child->move(shift);
    }
}

Barta::DynamicsDTOCollection& Barta::RigidCompositeObject::getDynamicsDTOs() {
    return this->dynamicsDtoCollection;
}

void Barta::RigidCompositeObject::rotate(
    const Quaternion& rotation
) {
    for (auto& child: this->children) {
        auto diff = DynamicsAwareInterface::getCurrentDynamics(*this).massCenter - DynamicsAwareInterface::getCurrentDynamics(*child).massCenter;

        child->move(diff);
        child->rotate(rotation);
        child->move(-diff);
    }
}

Barta::GraphicsDataAwareInterface::GraphicsDataList Barta::RigidCompositeObject::getGraphicsData() {
    GraphicsDataList list = {};
    for (auto child: this->children) { // TODO transforms
        auto childList = child->getGraphicsData();
        list.reserve(list.size() + childList.size());

        list.insert(list.end(), childList.begin(), childList.end());
    }

    return list;
}

void Barta::RigidCompositeObject::addNewChild(
    RigidObjectInterface* newChild
) {
    this->children.push_back(newChild);
    newChild->getDynamicsDTOs() = DynamicsDTOCollection{DynamicsDTO()};
}

Barta::RigidCompositeObject::~RigidCompositeObject() noexcept {
    for (auto child: this->children) {
        delete child;
    }
}
