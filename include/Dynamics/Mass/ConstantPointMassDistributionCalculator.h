#pragma once
#include "MassDistributionCalculatorInterface.h"
#include "Objects/Soft/SoftObject.h"
#include <pch.h>

namespace Barta::Dynamics::Mass {
class ConstantPointMassDistributionCalculator: public virtual MassDistributionCalculatorInterface {
public:
    ConstantPointMassDistributionCalculator() = default;

    void prepareMassDistribution(Objects::Soft::SoftObject& object) override;

    SoftBody::StiffnessMatrixType assembleInverseMassMatrix(const Objects::Soft::Mesh& mesh, const Objects::Soft::NodalVectorType& positions)
        override;
};
}
