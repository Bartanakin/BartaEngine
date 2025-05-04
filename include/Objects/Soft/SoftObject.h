#pragma once
#include "Graphics/GraphicsDataAwareInterface.h"
#include "Hitbox/HitboxAwareInterface.h"
#include <Dynamics/UpdateStrategy/DynamicsAwareConcept.h>
#include <Objects/Soft/Mesh.h>
#include <pch.h>

namespace Barta::Objects::Soft {
class SoftObject: public virtual GraphicsDataAwareInterface, public virtual HitboxAware {
    Mesh mesh;
    GraphicsData graphicsData;
    std::unique_ptr<HitboxInterface> hitbox;
    DynamicsDTOCollection dynamicsDTOCollection;

public:
    SoftObject(Mesh mesh, DynamicsDTO initialDynamics) noexcept;

    bool isToBeDeleted() const override;

    void move(const Vector& shift);

    DynamicsDTOCollection& getDynamicsDTOs();

    void rotate(const Quaternion& rotation);

    std::unique_ptr<const HitboxInterface> getHitbox() const override;

    GraphicsDataList getGraphicsData() override;

    Vector getForce(DynamicsDTOIteration positionIteration, DynamicsDTOIteration velocityIteration);

    Mesh& getMesh() noexcept;

    const Mesh& getMesh() const noexcept;
};

static_assert(Barta::Dynamics::UpdateStrategy::DynamicsAwareConcept<SoftObject>);

}
