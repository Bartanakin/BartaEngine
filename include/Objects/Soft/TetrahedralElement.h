#pragma once
#include <Objects/Soft/Node.h>
#include <pch.h>

namespace Barta::Objects::Soft {
class TetrahedralElement {
    std::array<Node*, 4> nodes;
    std::array<bool, 4> isFaceASurface;

public:
    static constexpr auto FACE_INDICES_CONTAINER = std::array<std::array<unsigned char, 3>, 4>({
        std::array<unsigned char, 3>{0, 1, 2},
        std::array<unsigned char, 3>{0, 3, 1},
        std::array<unsigned char, 3>{1, 3, 2},
        std::array<unsigned char, 3>{2, 3, 0},
    });
    TetrahedralElement(Node& n1, Node& n2, Node& n3, Node& n4) noexcept;

    void setIsFaceSurface(unsigned char index, bool isSurface);

    bool getIsFaceSurface(unsigned char index) const noexcept;

    const Node& operator[](unsigned char index) const noexcept;
};
}
