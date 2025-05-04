#pragma once
#include "SoftBodyDynamicsInterface.h"
#include <pch.h>

namespace Barta::Dynamics::SoftBody {
class StVenantKirchhoffDynamics: public virtual SoftBodyDynamicsInterface {
public:
    StiffnessMatrixType assembleTangentStiffnessMatrix(const Objects::Soft::Mesh& elements, const NodalVectorType& nodesPositions) override;

    NodalVectorType calculateNodalForces(const Objects::Soft::Mesh& elements, const NodalVectorType& nodesPositions) override;
};
}
