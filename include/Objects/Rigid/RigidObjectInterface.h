#pragma once

#include <Dynamics/UpdateStrategy/DynamicsAwareConcept.h>
#include <Graphics/GraphicsDataAwareInterface.h>
#include <Hitbox/HitboxAwareInterface.h>

namespace Barta {

class RigidObjectInterface: public virtual GraphicsDataAwareInterface, public virtual HitboxAware {
public:
    RigidObjectInterface() = default;
    virtual ~RigidObjectInterface() = default;

    virtual void move(const Vector& shift) = 0;

    virtual DynamicsDTOCollection& getDynamicsDTOs() = 0;

    virtual void rotate(const Quaternion& rotation) = 0;

    virtual Vector getForce(DynamicsDTOIteration positionIteration, DynamicsDTOIteration velocityIteration) = 0;

    static_assert(Barta::Dynamics::UpdateStrategy::DynamicsAwareConcept<RigidObjectInterface>);
};
}
