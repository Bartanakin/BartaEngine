#pragma once
#include <Objects/Soft/Node.h>
#include <Utilities/MatrixUtilities.h>
#include <pch.h>

namespace Barta::Objects::Soft {
using Barta::Utils::Matrix3Type;
using NodalVectorType = Eigen::VectorX<PrecisionType>;

class TetrahedralElement {
    std::array<unsigned int, 4> nodeIndices;
    std::array<bool, 4> isFaceASurface;
    Eigen::Matrix<PrecisionType, 3, 3> referenceShapeMatrix;

private:
    Eigen::Vector3<PrecisionType> retrieveNodePosition(const std::vector<Node>& nodes, const NodalVectorType& nodesPositions, unsigned int i) const;

public:
    static constexpr auto FACE_INDICES_CONTAINER = std::array<std::array<unsigned char, 3>, 4>({
        std::array<unsigned char, 3>{0, 1, 2},
        std::array<unsigned char, 3>{0, 3, 1},
        std::array<unsigned char, 3>{1, 3, 2},
        std::array<unsigned char, 3>{2, 3, 0},
    });
    TetrahedralElement(const std::vector<Node>& nodes, unsigned int n1, unsigned int n2, unsigned int n3, unsigned int n4) noexcept;

    void setIsFaceSurface(unsigned char index, bool isSurface);

    bool getIsFaceSurface(unsigned char index) const noexcept;

    const std::array<unsigned int, 4>& getNodeIndices() const noexcept;

    Matrix3Type getInverseReferenceShapeMatrix() const noexcept;

    Matrix3Type calculateShapeMatrix(const std::vector<Objects::Soft::Node>& nodes, const NodalVectorType& nodesPositions = NodalVectorType{0}) const;
};
}
