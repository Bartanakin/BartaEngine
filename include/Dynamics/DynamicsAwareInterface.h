#pragma once

#include "../Geometrics/Vector2f.h"
#include "../ReduceableList.h"
#include "../pch.h"
#include "DynamicsAwareListConcept.h"
#include "DynamicsDTO.h"
#include "DynamicsDTOCollection.h"
#include <BartaObjectInterface.h>

namespace Barta {

class DynamicsAwareInterface: public virtual BartaObjectInterface {
public:
    DynamicsAwareInterface() = default;
    virtual ~DynamicsAwareInterface() = default;

    using DynamicsAwareList = ReducibleList<std::list<DynamicsAwareInterface*>>;

    virtual void move(const Vector& shift) = 0;

    virtual void rotate(PrecisionType, const Point&) = 0;

    /**
     * @deprecated use getCurrentDynamicsData() or getNextDynamicsData() instead
     */
    virtual DynamicsDTOCollection& getDynamicsDTOs() = 0;

    virtual const DynamicsDTO& getCurrentDynamicsData() final { return this->getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT]; }

    virtual DynamicsDTO& getNextDynamicsData() final { return this->getDynamicsDTOs()[Barta::DynamicsDTOIteration::NEXT]; }
};

static_assert(DynamicsAwareConcept<DynamicsAwareInterface>);
}
