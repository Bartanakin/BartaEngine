#include <Objects/Soft/TetrahedralElement.h>

namespace Barta::Objects::Soft {
TetrahedralElement::TetrahedralElement(
    Node& n1,
    Node& n2,
    Node& n3,
    Node& n4
) noexcept:
    nodes({&n1, &n2, &n3, &n4}),
    isFaceASurface({false, false, false, false}) {}

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

const Node& TetrahedralElement::operator[](
    unsigned char index
) const noexcept {
    return *nodes[index];
}
}
