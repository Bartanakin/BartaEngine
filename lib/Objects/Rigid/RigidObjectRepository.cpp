//
// Created by barta on 03/03/2024.
//

#include <Objects/Rigid/RigidObjectRepository.h>
#include <Graphics/SFML_GraphicsBridge.h>
#include <Graphics/SpriteBuilder/RectangleWithColorsSpriteBuilder.h>
#include <Graphics/SpriteBuilder/SpriteMerger.h>
#include <Hitbox/AABB_Hitbox.h>
#include <Hitbox/CircleHitbox.h>
#include <Objects/Rigid/RigidObject.h>

Barta::RigidObjectRepository::RigidObjectRepository(
    ListManager& listManager,
    ObjectManagerInterface& objectManager
) noexcept:
    listManager(listManager),
    objectManager(objectManager) {}

Barta::RigidObjectInterface* Barta::RigidObjectRepository::addNewAABB(
    Vector2f size,
    Color color,
    bool infiniteMass
) {
    auto spriteBuilder = RectangleWithColorsSpriteBuilder();
    spriteBuilder.setVertex1({0.f, 0.f});
    spriteBuilder.setSize(size);
    spriteBuilder.setAllColors(color);
    auto merger = SpriteMerger();
    merger.addRectanglewithColors(spriteBuilder.build());
    auto aabb = new RigidObject(
        {
            Barta::SFML_GraphicsBridge::createNewTransformableInstance(),
            merger.merge(false),
            4
    },
        std::unique_ptr<HitboxInterface>(new AABB_Hitbox({{0.f, 0.f}, size})),
        {{0., 0.}, infiniteMass, infiniteMass ? 0.f : 1.f}
    );

    this->listManager.addObject(aabb);
    this->objectManager.addGraphicsObject(aabb);
    this->objectManager.addDynamicsObject(aabb);
    this->objectManager.addNewObject(aabb);

    return aabb;
}

Barta::RigidObjectInterface* Barta::RigidObjectRepository::addNewCircle(
    float radius,
    Color color
) {
    auto merger = SpriteMerger();
    merger.addCircleSprite(CircleSprite(Circle(radius, Vector2f(radius, radius)), color));
    auto circle = new RigidObject(
        {
            Barta::SFML_GraphicsBridge::createNewTransformableInstance(),
            merger.merge(false),
            4
    },
        std::unique_ptr<HitboxInterface>(new CircleHitbox({radius, {radius, radius}})),
        {{0., 0.}, false, 1.f}
    );

    this->listManager.addObject(circle);
    this->objectManager.addGraphicsObject(circle);
    this->objectManager.addDynamicsObject(circle);
    this->objectManager.addNewObject(circle);

    return circle;
}
