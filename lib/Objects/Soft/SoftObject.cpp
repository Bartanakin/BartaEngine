#include <Objects/Soft/SoftObject.h>
#include <Graphics/SpriteBuilder/SpriteMerger.h>
#include <Hitbox/NullHitbox.h>
#include <Utilities/DynamicsIteration.h>

namespace Barta::Objects::Soft {
SoftObject::SoftObject(
    Mesh mesh,
    DynamicsDTO initialDynamics
) noexcept:
    mesh(std::move(mesh)),
    dynamicsDTOCollection(initialDynamics) {}

bool SoftObject::isToBeDeleted() const {
    return false;
}

void SoftObject::move(
    const Vector& shift
) {
    Utils::extractCurrentDynamics(*this).massCenter += shift;
}

DynamicsDTOCollection& SoftObject::getDynamicsDTOs() {
    return this->dynamicsDTOCollection;
}

void SoftObject::rotate(
    const Quaternion& rotation
) {
    Utils::extractCurrentDynamics(*this).rotation *= rotation;
}

std::unique_ptr<const HitboxInterface> SoftObject::getHitbox() const {
    return std::make_unique<const NullHitbox>();
}

GraphicsDataAwareInterface::GraphicsDataList SoftObject::getGraphicsData() {
    this->graphicsData.transformation = Transformation::translation(Utils::extractCurrentDynamics(*this).massCenter.toVector())
                                        * Transformation::rotation(Utils::extractCurrentDynamics(*this).rotation) * Transformation::Identity();

    SpriteMerger merger;
    std::array<Color, 4> colors; // TODO manage colors in a nicer way
    colors[0] = {255, 0, 0};
    colors[1] = {255, 255, 0};
    colors[2] = {0, 255, 0};
    colors[3] = {0, 255, 255};
    for (const auto& element: this->mesh.elements) {
        for (unsigned char i = 0; i < TetrahedralElement::FACE_INDICES_CONTAINER.size(); i++) {
            if (!element.getIsFaceSurface(i)) {
                continue;
            }

            SpriteBuilder builder;
            // clang-format off
            builder.vertex1 = element[TetrahedralElement::FACE_INDICES_CONTAINER[i][0]].dynamicsDTOCollection[DynamicsDTOIteration::CURRENT].massCenter;
            builder.vertex2 = element[TetrahedralElement::FACE_INDICES_CONTAINER[i][1]].dynamicsDTOCollection[DynamicsDTOIteration::CURRENT].massCenter;
            builder.vertex3 = element[TetrahedralElement::FACE_INDICES_CONTAINER[i][2]].dynamicsDTOCollection[DynamicsDTOIteration::CURRENT].massCenter;
            // clang-format on
            builder.color = colors[i];

            merger.addTriangle(builder.buildTriangleSprite());
        }
    }

    this->graphicsData.resource = merger.merge(false);

    return {&this->graphicsData};
}

Vector SoftObject::getForce(
    DynamicsDTOIteration positionIteration,
    DynamicsDTOIteration velocityIteration
) {
    return Vector::Zero();
}

}
