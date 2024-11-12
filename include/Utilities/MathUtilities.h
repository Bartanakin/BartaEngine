#pragma once
#include "../pch.h"
#include "QuadraticEquation.h"

namespace Barta::Utils {
QuadraticEquation createQuadraticEquation(
    float A,
    float B,
    float C
) {
    return QuadraticEquation(A, B, C);
}
}
