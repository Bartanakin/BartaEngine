#pragma once
#include "Geometrics/TransformableInterface.h"
#include "Graphics/BartaSprite.h"

namespace Barta {

class BartaObjectInterface {
public:
    virtual ~BartaObjectInterface() noexcept = default;

    virtual bool isToBeDeleted() const = 0;
};
}
