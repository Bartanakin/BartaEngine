#include <Dynamics/Mass/ConstantPointMassDistributionCalculator.h>
#include "Objects/Soft/SoftObject.h"
#include "Utilities/DynamicsIteration.h"

namespace Barta::Dynamics::Mass {
void ConstantPointMassDistributionCalculator::prepareMassDistribution(
    Objects::Soft::SoftObject& object
) {
    auto massCenterTranslation = Vector::Zero();
    PrecisionType totalMass = 0.;
    unsigned int i = 0; // TODO change to range loop with index using std::view::enumerate
    for (const auto& node: object.getMesh().nodes) {
        auto& dynamicsData = node.dynamicsDTOCollection.dynamicsDTOs[DynamicsDTOIteration::NEXT];

        PrecisionType mass = 1. / dynamicsData.inverseMass;
        totalMass += mass;
        massCenterTranslation += mass * dynamicsData.massCenter.toVector();

        ++i;
    }

    massCenterTranslation /= totalMass;
    massCenterTranslation = massCenterTranslation.zeroised();
    i = 0; // TODO change to range loop with index using std::view::enumerate
    for (auto& node: object.getMesh().nodes) {
        auto& dynamicsData = node.dynamicsDTOCollection.dynamicsDTOs[DynamicsDTOIteration::NEXT];

        dynamicsData.massCenter -= massCenterTranslation;

        ++i;
    }

    Utils::extractNextDynamics(object).massCenter += Transformation::rotation(Utils::extractCurrentDynamics(object).rotation) * massCenterTranslation;
}

SoftBody::StiffnessMatrixType ConstantPointMassDistributionCalculator::assembleInverseMassMatrix(
    const Objects::Soft::Mesh& mesh,
    const Objects::Soft::NodalVectorType& positions
) {
    SoftBody::StiffnessMatrixType massMatrix = SoftBody::StiffnessMatrixType::Zero(mesh.getNodalVectorSize(), mesh.getNodalVectorSize());
    unsigned int i = 0;
    for (const auto& node: mesh.nodes) {
        if (node.isZeroDirichlet) {
            continue;
        }

        auto dynamicsData = node.dynamicsDTOCollection.dynamicsDTOs[DynamicsDTOIteration::CURRENT];

        massMatrix(3 * i, 3 * i) = dynamicsData.inverseMass;
        massMatrix(3 * i + 1, 3 * i + 1) = dynamicsData.inverseMass;
        massMatrix(3 * i + 2, 3 * i + 2) = dynamicsData.inverseMass;

        ++i;
    }

    return massMatrix;
}

}
