#pragma once
#include <Geometrics/Vector.h>
#include <pch.h>

namespace Barta {

struct DynamicsDifference {
    /**
     * @deprecated change to current/next state evaluation
     */
    DynamicsDifference(
        Vector velocity
    ):
        velocity(std::move(velocity)) {}

    DynamicsDifference& operator=(
        const DynamicsDifference& second
    ) {
        this->velocity = second.velocity;

        return *this;
    }

    DynamicsDifference(const DynamicsDifference& second) = default;

    DynamicsDifference operator-() const { return {-this->velocity}; }

    Vector velocity;
};

inline DynamicsDifference operator*(
    const Matrix& M,
    const DynamicsDifference& dynamicsDifference
) noexcept {
    return {M * dynamicsDifference.velocity};
}
}
