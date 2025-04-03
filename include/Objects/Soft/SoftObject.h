#pragma once
#include "Collisions/CollisionAwareInterface.h"
#include "Graphics/GraphicsDataAwareInterface.h"
#include <Objects/Soft/Mesh.h>
#include <pch.h>

namespace Barta::Objects::Soft {
class SoftObject: public virtual GraphicsDataAwareInterface, public virtual CollisionAwareInterface {
    Mesh mesh;
    GraphicsData graphicsData;
    std::unique_ptr<HitboxInterface> hitbox;
    DynamicsDTOCollection dynamicsDTOCollection;

public:
    SoftObject(Mesh mesh, DynamicsDTO initialDynamics) noexcept;

    bool isToBeDeleted() const override;

    void move(const Vector& shift) override;

    DynamicsDTOCollection& getDynamicsDTOs() override;

    void rotate(const Quaternion& rotation) override;

    std::unique_ptr<const HitboxInterface> getHitbox() const override;

    GraphicsDataList getGraphicsData() override;
};
}
