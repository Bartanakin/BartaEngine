#include <Objects/Soft/SoftObject.h>
#include "Hitbox/TriangleAggregateHitbox.h"
#include <Graphics/SpriteBuilder/SpriteMerger.h>
#include <Hitbox/NullHitbox.h>
#include <Utilities/DynamicsIteration.h>

namespace Barta::Objects::Soft {
SoftObject::SoftObject(
    Mesh mesh,
    DynamicsDTO initialDynamics
) noexcept:
    mesh(std::move(mesh)),
    dynamicsDTOCollection(initialDynamics) {
    for (const auto& element: this->mesh.elements) {
        for (unsigned char i = 0; i < TetrahedralElement::FACE_INDICES_CONTAINER.size(); i++) {
            if (!element.getIsFaceSurface(i)) {
                continue;
            }

            std::array<unsigned int, 3> triangleIndices;
            triangleIndices[0] = element.getNodeIndices()[TetrahedralElement::FACE_INDICES_CONTAINER[i][0]];
            triangleIndices[1] = element.getNodeIndices()[TetrahedralElement::FACE_INDICES_CONTAINER[i][1]];
            triangleIndices[2] = element.getNodeIndices()[TetrahedralElement::FACE_INDICES_CONTAINER[i][2]];

            this->surfaceTriangleIndices.push_back(triangleIndices);
        }
    }
}

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
    auto transformation = this->dynamicsDTOCollection[DynamicsDTOIteration::NEXT].getTransformation();
    std::vector<Triangle> triangles;
    triangles.reserve(this->surfaceTriangleIndices.size());
    for (const auto& triangleIndices: this->surfaceTriangleIndices) {
        triangles.emplace_back(
            transformation.getMatrix() * this->mesh.nodes[triangleIndices[0]].dynamicsDTOCollection[DynamicsDTOIteration::NEXT].massCenter,
            transformation.getMatrix() * this->mesh.nodes[triangleIndices[1]].dynamicsDTOCollection[DynamicsDTOIteration::NEXT].massCenter,
            transformation.getMatrix() * this->mesh.nodes[triangleIndices[2]].dynamicsDTOCollection[DynamicsDTOIteration::NEXT].massCenter
        );
    }

    return std::make_unique<const Hitbox::TriangleAggregateHitbox>(
        Geometrics::BartaShapes::TriangleSurface(std::move(triangles), this->surfaceTriangleIndices)
    );
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
    for (const auto triangleIndices: this->surfaceTriangleIndices) {
        SpriteBuilder builder;
        // clang-format off
        builder.vertex1 = this->mesh.nodes[triangleIndices[0]].dynamicsDTOCollection[DynamicsDTOIteration::CURRENT].massCenter;
        builder.vertex2 = this->mesh.nodes[triangleIndices[1]].dynamicsDTOCollection[DynamicsDTOIteration::CURRENT].massCenter;
        builder.vertex3 = this->mesh.nodes[triangleIndices[2]].dynamicsDTOCollection[DynamicsDTOIteration::CURRENT].massCenter;
        // clang-format on

        // coloring TODO remove, this is just for tests
        for (auto& [vertex, color]: std::vector<std::pair<Point&, Color&>>{
                 {this->mesh.nodes[triangleIndices[0]].restPosition, builder.color1},
                 {this->mesh.nodes[triangleIndices[1]].restPosition, builder.color2},
                 {this->mesh.nodes[triangleIndices[2]].restPosition, builder.color3}
        }) {
            color.r = 255. * (20 + vertex.x()) / 40.;
            color.g = 255. * (20 + vertex.y()) / 40.;
            color.b = 255. * vertex.z() / 60.;
            color.a = 0.;
        }

        merger.addTriangle(builder.buildTriangleWithColorsSprite());
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

Mesh& SoftObject::getMesh() noexcept {
    return this->mesh;
}

const Mesh& SoftObject::getMesh() const noexcept {
    return this->mesh;
}

}
