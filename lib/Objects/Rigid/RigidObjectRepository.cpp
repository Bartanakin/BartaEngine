//
// Created by barta on 03/03/2024.
//

#include <Graphics/SpriteBuilder/RectangleWithColorsSpriteBuilder.h>
#include <Graphics/SpriteBuilder/SpriteMerger.h>
#include <Hitbox/AABB_Hitbox.h>
#include <Graphics/SFML_GraphicsBridge.h>
#include <Hitbox/CircleHitbox.h>
#include <Objects/Rigid/RigidObjectRepository.h>

Barta::RigidObjectRepository::RigidObjectRepository(
    Barta::ListManager &listManager,
    Barta::ObjectManagerInterface &objectManager
) noexcept :
    listManager(listManager),
    objectManager(objectManager)
{}

Barta::RigidObjectInterface *Barta::RigidObjectRepository::addNewAABB(
    Barta::Vector2f size,
    Barta::Color color,
    bool infiniteMass
) {
    auto spriteBuilder = Barta::RectangleWithColorsSpriteBuilder();
    spriteBuilder.setVertex1({0.f, 0.f});
    spriteBuilder.setSize(size);
    spriteBuilder.setAllColors(color);
    auto merger = Barta::SpriteMerger();
    merger.addRectanglewithColors(spriteBuilder.build());
    auto aabb = new Barta::RigidObject(
        {
            Barta::SFML_GraphicsBridge::createNewTransformableInstance(),
            merger.merge(false),
            4
        },
        std::unique_ptr<Barta::HitboxInterface>(new Barta::AABB_Hitbox({{0.f, 0.f}, size})),
        {{0., 0.}, infiniteMass, infiniteMass ? 0.f : 1.f}
    );

    this->listManager.addObject(aabb);
    this->objectManager.addGraphicsObject(static_cast<Barta::GraphicsDataAwareInterface*>(aabb));
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(aabb));
    this->objectManager.addNewObject(static_cast<Barta::BartaObjectInterface*>(aabb));

    return aabb;
}

Barta::RigidObjectInterface *Barta::RigidObjectRepository::addNewCircle(float radius, Barta::Color color) {
    auto merger = Barta::SpriteMerger();
    merger.addCircleSprite(Barta::CircleSprite(
        Barta::Circle(
            radius,
            Barta::Vector2f(radius, radius)
        ),
        color
    ));
    auto circle = new Barta::RigidObject(
        {
            Barta::SFML_GraphicsBridge::createNewTransformableInstance(),
            merger.merge(false),
            4
        },
        std::unique_ptr<Barta::HitboxInterface>(new Barta::CircleHitbox({radius, {radius, radius}})),
        {{0., 0.}, false, 1.f}
    );

    this->listManager.addObject(circle);
    this->objectManager.addGraphicsObject(static_cast<Barta::GraphicsDataAwareInterface*>(circle));
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(circle));
    this->objectManager.addNewObject(static_cast<Barta::BartaObjectInterface*>(circle));

    return circle;
}
