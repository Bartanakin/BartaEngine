#include <Objects/Soft/Mesh.h>

namespace Barta::Objects::Soft {
Mesh::Mesh(
    std::vector<Node> nodes,
    std::vector<TetrahedralElement> elements
) noexcept:
    nodes(std::move(nodes)),
    elements(std::move(elements)),
    dirichletNodeCount(0) {}

}
