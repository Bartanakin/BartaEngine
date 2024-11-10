#pragma once
#include "../Geometrics/Math/EquationInterface.h"
#include "../Geometrics/Math/QuadraticEquation.h"
#include "../pch.h"

namespace Barta::Utils {
std::unique_ptr<EquationInterface> createQuadraticEquation(
    float A,
    float B,
    float C
) {
    return std::unique_ptr<EquationInterface>(new QuadraticEquation(A, B, C));
}
}
