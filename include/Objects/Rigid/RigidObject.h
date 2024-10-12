#pragma once

#include <BartaObjectInterface.h>
#include <Collisions/CollisionAwareInterface.h>
#include "Graphics/GraphicsDataAwareInterface.h"
#include "RigidObjectInterface.h"

namespace Barta {

    class RigidObject : public virtual RigidObjectInterface {
    public:
        RigidObject(
            GraphicsData graphicsData,
            std::unique_ptr<HitboxInterface> hitbox,
            DynamicsDTO dynamicsDto
        );
        ~RigidObject() noexcept = default;

        bool isToBeDeleted() const override { return false; };

        GraphicsDataList getGraphicsData() override;

        std::unique_ptr<const HitboxInterface> getHitbox() const override;

        void move( const Vector2f& shift ) override;

        DynamicsDTO& getDynamicsDTO() override;

        inline void rotate(float, Vector2f) override;

    protected:
        GraphicsData graphicsData;
        std::unique_ptr<HitboxInterface> hitbox;
        DynamicsDTO dynamicsDTO;
    };
}