#pragma once
#include "Dynamics/SoftBody/SoftBodyDynamicsInterface.h"
#include "Objects/Soft/Mesh.h"
#include "Objects/Soft/SoftObject.h"
#include <pch.h>

namespace Barta::Dynamics::Mass {
class MassDistributionCalculatorInterface {
public:
    MassDistributionCalculatorInterface() noexcept = default;
    virtual ~MassDistributionCalculatorInterface() noexcept = default;

    virtual void prepareMassDistribution(Objects::Soft::SoftObject& object) = 0;

    virtual SoftBody::StiffnessMatrixType assembleInverseMassMatrix(
        const Objects::Soft::Mesh& mesh,
        const Objects::Soft::NodalVectorType& positions
    ) = 0;
};
}
