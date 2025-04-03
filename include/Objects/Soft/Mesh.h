#pragma once
#include <Objects/Soft/Node.h>
#include <Objects/Soft/TetrahedralElement.h>
#include <pch.h>

namespace Barta::Objects::Soft {
struct Mesh {
    std::vector<Node> nodes;
    std::vector<TetrahedralElement> elements;

    Mesh(std::vector<Node> nodes, std::vector<TetrahedralElement> elements) noexcept;
};
}
