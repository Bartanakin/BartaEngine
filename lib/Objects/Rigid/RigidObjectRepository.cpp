//
// Created by barta on 03/03/2024.
//

#include <Objects/Rigid/RigidObjectRepository.h>
#include "Graphics/GraphicsDataTransformer.h"
#include "Hitbox/OBB_Hitbox.h"
#include <Graphics/SFML_GraphicsBridge.h>
#include <Graphics/SpriteBuilder/RectangleWithColorsSpriteBuilder.h>
#include <Graphics/SpriteBuilder/SpriteMerger.h>
#include <Hitbox/AABB_Hitbox.h>
#include <Hitbox/CircleHitbox.h>
#include <Objects/Rigid/RigidObject.h>

namespace Barta {
RigidObjectRepository::RigidObjectRepository(
    ListManager& listManager,
    ObjectManagerInterface& objectManager
) noexcept:
    listManager(listManager),
    objectManager(objectManager) {}

RigidObjectInterface* RigidObjectRepository::addNewAABB(
    Vector size,
    Color color,
    bool infiniteMass
) {
    auto spriteBuilder = RectangleWithColorsSpriteBuilder();
    spriteBuilder.setVertex1({0.f, 0.f, 0.f});
    spriteBuilder.setSize(size);
    spriteBuilder.setAllColors(color);
    auto merger = SpriteMerger();
    merger.addRectangleWithColors(spriteBuilder.build());
    auto aabb = new RigidObject(
        {
            Transformation::Identity(),
            merger.merge(false),
            4
    },
        std::make_unique<AABB_Hitbox>(AABB({0.f, 0.f, 0.f}, size)),
        {{0., 0.}, infiniteMass, infiniteMass ? 0.f : 1.f}
    );

    this->listManager.addObject(aabb);
    this->objectManager.addGraphicsObject(aabb);
    this->objectManager.addDynamicsObject(aabb);
    this->objectManager.addNewObject(aabb);

    return aabb;
}

RigidObjectInterface* RigidObjectRepository::addNewCircle(
    float radius,
    Color color
) {
    auto merger = SpriteMerger();
    merger.addCircleSprite(CircleSprite(Circle(radius, Point(radius, radius, 0.f)), color));
    auto circle = new RigidObject(
        {
            Transformation::Identity(),
            merger.merge(false),
            4
    },
        std::make_unique<CircleHitbox>(Circle(radius, {radius, radius, 0.f})),
        {{0., 0.}, false, 1.f}
    );

    this->listManager.addObject(circle);
    this->objectManager.addGraphicsObject(circle);
    this->objectManager.addDynamicsObject(circle);
    this->objectManager.addNewObject(circle);

    return circle;
}

RigidObjectInterface* RigidObjectRepository::addNewOBB(
    Vector size,
    PrecisionType rotation,
    Color color
) {
    auto transformer = GraphicsDataTransformer(color);
    auto obb = OBB{Point::Zero(), size, rotation};
    auto obbObject = new RigidObject(
        transformer.fromOBB(obb),
        std::make_unique<OBB_Hitbox>(obb),
        {
            {0., 0.},
            false,
            1.f
    }
    );

    this->listManager.addObject(obbObject);
    this->objectManager.addGraphicsObject(obbObject);
    this->objectManager.addDynamicsObject(obbObject);
    this->objectManager.addNewObject(obbObject);

    return obbObject;
}
}
