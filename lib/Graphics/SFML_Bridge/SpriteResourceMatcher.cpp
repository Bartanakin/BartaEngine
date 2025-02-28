#include <Graphics/SFML_Bridge/SpriteResourceMatcher.h>
#include <Geometrics/Transformation.h>
#include <pch.h>

Barta::SpriteResourceMatcher::SpriteResourceMatcher(
    std::unique_ptr<ResourceContainerInterface> resourceContainer
):
    sf_spriteMap({}),
    resourceContainer(std::move(resourceContainer)),
    nullDrawableObject({}) {}

Barta::SpriteResourceMatcher::~SpriteResourceMatcher() {
    for (auto sprite: this->sf_spriteMap) {
        delete sprite.second;
    }
}

void Barta::SpriteResourceMatcher::matchResource(
    const void* hash,
    const int resource
) {
    if (!this->resourceContainer->hasTexture(resource)) {
        return;
    }

    sf::Sprite* sprite = nullptr;
    if (this->sf_spriteMap.count(hash)) {
        sprite = this->sf_spriteMap.at(hash);
    } else {
        sprite = new sf::Sprite();
        this->sf_spriteMap[hash] = sprite;
    }

    sprite->setTexture(this->resourceContainer->getTexture(resource));
    sprite->setTextureRect(this->resourceContainer->getTextureRect(resource));
}

const sf::Drawable& Barta::SpriteResourceMatcher::matchAndTransform(
    const void* hash,
    const Transformation& transformation
) const {
    if (!this->sf_spriteMap.count(hash)) {
        return this->nullDrawableObject;
    }

    auto sprite = this->sf_spriteMap.at(hash);
    sprite->setPosition({transformation.getTranslation().x(), transformation.getTranslation().y()});
    auto rotation = transformation.getRotation();

    sprite->setRotation(std::abs(rotation.z()) / rotation.z() * rotation.w() * 180.f / M_PI);

    return *sprite;
}

void Barta::SpriteResourceMatcher::drop(
    const void* hash
) {
    if (!this->sf_spriteMap.count(hash)) {
        return;
    }

    auto object = this->sf_spriteMap.at(hash);
    this->sf_spriteMap.erase(hash);
    delete object;
}
