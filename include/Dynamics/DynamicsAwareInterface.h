#pragma once

#include <BartaObjectInterface.h>
#include <Dynamics/DynamicsAwareListConcept.h>
#include <Dynamics/DynamicsDTOCollection.h>
#include <ReduceableList.h>
#include <pch.h>

namespace Barta {

class DynamicsAwareInterface: public virtual BartaObjectInterface {
public:
    DynamicsAwareInterface() = default;
    virtual ~DynamicsAwareInterface() = default;

    using DynamicsAwareList = ReducibleList<std::list<DynamicsAwareInterface*>>;

    virtual void move(const Vector& shift) = 0;

    virtual void rotate(const Quaternion& rotation) = 0;

    virtual DynamicsDTOCollection& getDynamicsDTOs() = 0;

    // helpers:
    static DynamicsDTO& getCurrentDynamics(
        DynamicsAwareInterface& obj
    ) {
        return obj.getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT];
    }

    static DynamicsDTO& getNextDynamics(
        DynamicsAwareInterface& obj
    ) {
        return obj.getDynamicsDTOs()[Barta::DynamicsDTOIteration::NEXT];
    }
};

static_assert(DynamicsAwareConcept<DynamicsAwareInterface>);
}
