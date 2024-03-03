#pragma once

#include <BartaObject.h>
#include <Collisions/CollisionAwareInterface.h>
#include <DeletableObject.h>

namespace Barta {

    class RigidObject :
        public BartaObjectInterface,
        public CollisionAwareInterface,
        public DeletableObject {
    public:
        RigidObject(
            std::unique_ptr<TransformableInterface> transformable,
            std::unique_ptr<HitboxInterface> hitbox,
            DynamicsDTO dynamicsDto
        );
        ~RigidObject() noexcept = default;

        bool isToBeDeleted() const override { return DeletableObject::isToBeDeleted(); };

        const TransformableInterface& getTransformable() const override;

        const BartaSprite* getResource() noexcept override;

        std::unique_ptr<const HitboxInterface> getHitbox() const override;

        void move( const Vector2f& shift ) override;

        RigidObject* setVelocity(const Vector2f& velocity);

        const DynamicsDTO& getDynamicsDTO() const override;

        void setDynamicsDTO( const DynamicsDTO& ) override;

        inline virtual void rotate(float, Vector2f) override {}

        int getZIndex() const override;

        void setResource(BartaSprite resource);

    protected:
        std::unique_ptr<TransformableInterface> transformable;
        std::unique_ptr<HitboxInterface> hitbox;
        DynamicsDTO dynamicsDTO;

        BartaSprite resource;
    };
}