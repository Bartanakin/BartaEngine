//
// Created by bartanakin on 11/7/24.
//

#pragma once
#include "DynamicsDTO.h"
#include <array>

namespace Barta {

enum DynamicsDTOIteration {
    CURRENT = 0,
    NEXT = 1
};

class DynamicsDTOCollection {
private:
    static constexpr size_t NUMBER_OF_ITERATIONS = 2;

public:
    using DynamicsDTOArray = std::array<DynamicsDTO, NUMBER_OF_ITERATIONS>;
    DynamicsDTOArray dynamicsDTOs;

    explicit DynamicsDTOCollection(
        std::array<DynamicsDTO, NUMBER_OF_ITERATIONS> dynamicsDTOs
    ):
        dynamicsDTOs(std::move(dynamicsDTOs)) {}

    explicit DynamicsDTOCollection(
        DynamicsDTO dynamicsDTO
    ):
        dynamicsDTOs({dynamicsDTO, dynamicsDTO}) {}

    DynamicsDTO& operator[](
        const DynamicsDTOIteration& i
    ) {
        return this->dynamicsDTOs[static_cast<size_t>(i)];
    }

    const DynamicsDTO& operator[](
        const DynamicsDTOIteration& i
    ) const {
        return this->dynamicsDTOs[static_cast<size_t>(i)];
    }

    void forward() {
        this->operator[](DynamicsDTOIteration::CURRENT) = this->operator[](DynamicsDTOIteration::NEXT);
        this->operator[](DynamicsDTOIteration::CURRENT).allowedDirections = {};
    }
};
}
