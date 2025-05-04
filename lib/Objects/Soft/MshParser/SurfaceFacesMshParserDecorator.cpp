#include <Objects/Soft/MshParser/SurfaceFacesMshParserDecorator.h>

namespace Barta::Objects::Soft::MshParser {
SurfaceFacesMshParserDecorator::SurfaceFacesMshParserDecorator(
    MshDataParserInterface& decorated
) noexcept:
    decorated(decorated) {}

Mesh SurfaceFacesMshParserDecorator::parse(
    const MshData& mshData
) const {
    auto mesh = this->decorated.parse(mshData);

    std::map<std::array<unsigned int, 3>, std::pair<TetrahedralElement*, unsigned char>> facesFound;
    for (auto& elem: mesh.elements) {
        for (unsigned char i = 0; i < TetrahedralElement::FACE_INDICES_CONTAINER.size(); ++i) {
            std::array<unsigned int, 3> faceIndexPointers;
            faceIndexPointers[0] = elem.getNodeIndices()[TetrahedralElement::FACE_INDICES_CONTAINER[i][0]];
            faceIndexPointers[1] = elem.getNodeIndices()[TetrahedralElement::FACE_INDICES_CONTAINER[i][1]];
            faceIndexPointers[2] = elem.getNodeIndices()[TetrahedralElement::FACE_INDICES_CONTAINER[i][2]];
            std::sort(faceIndexPointers.begin(), faceIndexPointers.end());
            if (facesFound.contains(faceIndexPointers)) {
                facesFound.erase(faceIndexPointers);
            } else {
                facesFound[faceIndexPointers] = {&elem, i};
            }
        }
    }

    for (auto& [elem, faceIndex]: facesFound | std::views::values) {
        elem->setIsFaceSurface(faceIndex, true);
    }

    return mesh;
}
}
