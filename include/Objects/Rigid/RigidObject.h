#pragma once

#include "Graphics/GraphicsDataAwareInterface.h"
#include "RigidObjectInterface.h"
#include <BartaObjectInterface.h>
#include <Collisions/CollisionAwareInterface.h>

namespace Barta {

class RigidObject: public virtual RigidObjectInterface {
public:
    RigidObject(GraphicsData graphicsData, std::unique_ptr<HitboxInterface> hitbox, DynamicsDTO dynamicsDto);
    ~RigidObject() noexcept override = default;

    bool isToBeDeleted() const override { return false; }

    GraphicsDataList getGraphicsData() override;

    std::unique_ptr<const HitboxInterface> getHitbox() const override;

    void move(const Vector2f& shift) override;

    DynamicsDTO& getDynamicsDTO() override;

    inline void rotate(float, Vector2f) override;
    void rotate(float);
    float getRotation() const;
    void setRotation(float angle);

protected:
    GraphicsData graphicsData;
    std::unique_ptr<HitboxInterface> hitbox;
    DynamicsDTO dynamicsDTO;
};
}
