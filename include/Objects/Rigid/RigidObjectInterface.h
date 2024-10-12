#pragma once

#include <BartaObjectInterface.h>
#include <Collisions/CollisionAwareInterface.h>
#include <Graphics/GraphicsDataAwareInterface.h>

namespace Barta {

    class RigidObjectInterface :
        public virtual GraphicsDataAwareInterface,
        public virtual CollisionAwareInterface
    {
    public:
        RigidObjectInterface() = default;
        virtual ~RigidObjectInterface() = default;
    };
}