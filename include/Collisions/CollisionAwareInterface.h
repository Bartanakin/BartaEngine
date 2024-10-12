#pragma once
#include "../Dynamics/DynamicsAwareInterface.h"
#include "../Hitbox/HitboxAwareInterface.h"

namespace Barta {

class CollisionAwareInterface: public virtual HitboxAware, public virtual DynamicsAwareInterface {
public:
    CollisionAwareInterface() = default;
    virtual ~CollisionAwareInterface() = default;
};

}
