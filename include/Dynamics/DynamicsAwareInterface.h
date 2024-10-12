#pragma once

#include "../Geometrics/Vector2f.h"
#include "../ReduceableList.h"
#include "../pch.h"
#include "DynamicsDTO.h"
#include <BartaObjectInterface.h>

namespace Barta {

class DynamicsAwareInterface: public virtual BartaObjectInterface {
public:
    DynamicsAwareInterface() = default;
    virtual ~DynamicsAwareInterface() = default;

    using DynamicsAwareList = ReducibleList<std::list<DynamicsAwareInterface*>>;

    virtual void move(const Vector2f& shift) = 0;

    virtual void rotate(float, Vector2f) = 0;

    virtual DynamicsDTO& getDynamicsDTO() = 0;
};
}
