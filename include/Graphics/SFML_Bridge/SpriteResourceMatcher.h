#pragma once
#include <Geometrics/Transformation.h>
#include <Graphics/SFML_Bridge/NullDrawableObject.h>
#include <Graphics/SFML_Bridge/ResourceContainerInterface.h>
#include <Graphics/SFML_Bridge/ResourceMatcherInterface.h>
#include <pch.h>

namespace Barta {
class SpriteResourceMatcher: public RecourseMatcherInterface {
public:
    SpriteResourceMatcher(std::unique_ptr<ResourceContainerInterface> resourceContainer);
    virtual ~SpriteResourceMatcher();

    void matchResource(const void* hash, int resource) override;
    const sf::Drawable& matchAndTransform(const void* hash, const Transformation& transformation) const override;
    void drop(const void* hash) override;

private:
    std::unordered_map<const void*, sf::Sprite*> sf_spriteMap;
    std::unique_ptr<ResourceContainerInterface> resourceContainer;

    NullDrawableObject nullDrawableObject;
};
}
