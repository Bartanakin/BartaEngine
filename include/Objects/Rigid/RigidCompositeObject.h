#pragma once

#include <Collisions/CollisionAwareInterface.h>
#include <Objects/Rigid/RigidObjectInterface.h>

namespace Barta {

class RigidCompositeObject: public virtual RigidObjectInterface {
public:
    RigidCompositeObject(
        std::unique_ptr<TransformableInterface> transformable,
        DynamicsDTO dynamicsDto,
        std::vector<RigidObjectInterface*> children = {}
    );
    ~RigidCompositeObject() noexcept override;

    bool isToBeDeleted() const override;

    GraphicsDataList getGraphicsData() override;

    std::unique_ptr<const HitboxInterface> getHitbox() const override;

    void move(const Vector2f& shift) override;

    DynamicsDTOCollection& getDynamicsDTOs() override;

    inline void rotate(float, Vector2f) override;

    inline void addNewChild(RigidObjectInterface*);

protected:
    std::vector<RigidObjectInterface*> children;
    DynamicsDTOCollection dynamicsDtoCollection;
    std::unique_ptr<TransformableInterface> transformable;
};
}
