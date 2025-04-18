#pragma once

#include "Graphics/GraphicsDataAwareInterface.h"
#include "RigidObjectInterface.h"

namespace Barta {

class RigidObject: public virtual RigidObjectInterface {
public:
    RigidObject(GraphicsData graphicsData, std::unique_ptr<HitboxInterface> hitbox, DynamicsDTO dynamicsDto);
    ~RigidObject() noexcept override = default;

    bool isToBeDeleted() const override { return false; }

    GraphicsDataList getGraphicsData() override;

    std::unique_ptr<const HitboxInterface> getHitbox() const override;

    void move(const Vector& shift) override;

    DynamicsDTOCollection& getDynamicsDTOs() override;

    void rotate(const Quaternion& rotation) override;

    Vector getForce(DynamicsDTOIteration positionIteration, DynamicsDTOIteration velocityIteration) override;

protected:
    GraphicsData graphicsData;
    std::unique_ptr<HitboxInterface> hitbox;
    DynamicsDTOCollection dynamicsDTOCollection;
};

static_assert(Barta::Dynamics::UpdateStrategy::DynamicsAwareConcept<RigidObject>);
}
