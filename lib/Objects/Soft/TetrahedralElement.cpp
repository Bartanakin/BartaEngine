#include <Objects/Soft/TetrahedralElement.h>

namespace Barta::Objects::Soft {

TetrahedralElement::TetrahedralElement(
    const std::vector<Node>& nodes,
    unsigned int n1,
    unsigned int n2,
    unsigned int n3,
    unsigned int n4
) noexcept:
    nodeIndices({n1, n2, n3, n4}),
    isFaceASurface({false, false, false, false}),
    referenceShapeMatrix(this->calculateShapeMatrix(nodes).inverse()) {}

void TetrahedralElement::setIsFaceSurface(
    unsigned char index,
    bool isSurface
) {
    this->isFaceASurface[index] = isSurface;
}

bool TetrahedralElement::getIsFaceSurface(
    unsigned char index
) const noexcept {
    return this->isFaceASurface[index];
}

const std::array<unsigned int, 4>& TetrahedralElement::getNodeIndices() const noexcept {
    return this->nodeIndices;
}

Matrix3Type TetrahedralElement::getInverseReferenceShapeMatrix() const noexcept {
    return this->referenceShapeMatrix;
}

Eigen::Vector3<PrecisionType> TetrahedralElement::retrieveNodePosition(
    const std::vector<Objects::Soft::Node>& nodes,
    const NodalVectorType& nodesPositions,
    unsigned int i
) const {
    if (3 * this->nodeIndices[i] >= nodesPositions.size()) {
        Eigen::Vector3<PrecisionType> u;
        auto u_Dirichlet = nodes[this->nodeIndices[i]].dynamicsDTOCollection[DynamicsDTOIteration::CURRENT].massCenter;

        u.x() = u_Dirichlet.x();
        u.y() = u_Dirichlet.y();
        u.z() = u_Dirichlet.z();

        return u;
    }

    return nodesPositions.block<3, 1>(3 * this->nodeIndices[i], 0);
}

Matrix3Type TetrahedralElement::calculateShapeMatrix(
    const std::vector<Objects::Soft::Node>& nodes,
    const NodalVectorType& nodesPositions
) const {
    Matrix3Type result;
    auto u_3 = this->retrieveNodePosition(nodes, nodesPositions, 3);

    for (unsigned int i = 0; i < 3; i++) {
        auto u_i = this->retrieveNodePosition(nodes, nodesPositions, i);

        result.block<3, 1>(0, i) = u_i - u_3;
    }

    return result;
}
}
