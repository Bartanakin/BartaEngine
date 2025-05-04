#pragma once
#include <Objects/Soft/Node.h>
#include <Objects/Soft/TetrahedralElement.h>
#include <pch.h>

namespace Barta::Objects::Soft {
struct Mesh {
    std::vector<Node> nodes; // All Dirichlet nodes are in the back of the vector
    std::vector<TetrahedralElement> elements;
    unsigned int dirichletNodeCount;

    Mesh() = default;
    Mesh(std::vector<Node> nodes, std::vector<TetrahedralElement> elements) noexcept;

    size_t getNodalVectorSize() const noexcept { return 3 * (this->nodes.size() - this->dirichletNodeCount); }
};
}
