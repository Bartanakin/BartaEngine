#pragma once
#include <Geometrics/Point.h>
#include <pch.h>

namespace Barta::Utils {

using Matrix3Type = Eigen::Matrix<PrecisionType, 3, 3>;
using Matrix9Type = Eigen::Matrix<PrecisionType, 9, 9>;
using Matrix12Type = Eigen::Matrix<PrecisionType, 12, 12>;

Matrix9Type createEquationFromAXB(const Matrix3Type& A, const Matrix3Type& B);

Matrix9Type createEquationFromTrace(const Matrix3Type& A, const Matrix3Type& B, const Matrix3Type& C);

Matrix12Type create12MatrixFrom9MatrixAndThirdNewtonLaw(const Matrix9Type& M9);
}
