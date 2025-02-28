#pragma once

namespace Barta {

class BartaObjectInterface {
public:
    virtual ~BartaObjectInterface() noexcept = default;

    virtual bool isToBeDeleted() const = 0;
};
}
