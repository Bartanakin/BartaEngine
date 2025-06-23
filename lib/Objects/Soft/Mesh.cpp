#include <Objects/Soft/Mesh.h>

namespace Barta::Objects::Soft {
Mesh::Mesh(
    std::vector<Node> nodes,
    std::vector<TetrahedralElement> elements
) noexcept:
    nodes(std::move(nodes)),
    elements(std::move(elements)),
    dirichletNodeCount(0) {}

NodalVectorType Mesh::collectPositions(
    DynamicsDTOIteration iteration
) const {
    NodalVectorType positions = NodalVectorType::Zero(this->getNodalVectorSize());
    unsigned int i = 0;
    for (const auto& node: this->nodes) {
        if (node.isZeroDirichlet) {
            break;
        }

        const auto& dynamicsData = node.dynamicsDTOCollection.dynamicsDTOs[iteration];

        positions[3 * i + 0] = dynamicsData.massCenter.x();
        positions[3 * i + 1] = dynamicsData.massCenter.y();
        positions[3 * i + 2] = dynamicsData.massCenter.z();

        ++i;
    }

    return positions;
}

NodalVectorType Mesh::collectVelocities(
    DynamicsDTOIteration iteration
) const {
    NodalVectorType velocities = NodalVectorType::Zero(this->getNodalVectorSize());
    unsigned int i = 0;
    for (const auto& node: this->nodes) {
        if (node.isZeroDirichlet) {
            break;
        }

        const auto& dynamicsData = node.dynamicsDTOCollection.dynamicsDTOs[iteration];

        velocities[3 * i + 0] = dynamicsData.velocity.x();
        velocities[3 * i + 1] = dynamicsData.velocity.y();
        velocities[3 * i + 2] = dynamicsData.velocity.z();

        ++i;
    }

    return velocities;
}

void Mesh::updateNextDynamics(
    const NodalVectorType& positions,
    const NodalVectorType& velocities
) {
    unsigned int i = 0;
    for (auto& node: this->nodes) {
        if (node.isZeroDirichlet) {
            continue;
        }

        auto& dynamicsData = node.dynamicsDTOCollection.dynamicsDTOs[DynamicsDTOIteration::NEXT];

        dynamicsData.massCenter.x() = positions[3 * i];
        dynamicsData.massCenter.y() = positions[3 * i + 1];
        dynamicsData.massCenter.z() = positions[3 * i + 2];

        dynamicsData.velocity.x() = velocities[3 * i];
        dynamicsData.velocity.y() = velocities[3 * i + 1];
        dynamicsData.velocity.z() = velocities[3 * i + 2];
        dynamicsData.velocity = dynamicsData.velocity.zeroised();

        ++i;
    }
}

}
