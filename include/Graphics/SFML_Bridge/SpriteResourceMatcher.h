#pragma once
#include "../../pch.h"
#include "ResourceMatcherInterface.h"
#include "ResourceContainerInterface.h"
#include "NullDrawableObject.h"

namespace Barta{
	class SpriteResourceMatcher : public RecourseMatcherInterface{
	public:
		SpriteResourceMatcher( std::unique_ptr<ResourceContainerInterface> resourceContainer );
		virtual ~SpriteResourceMatcher();

		void matchResource( const void* hash, const int resource ) override;
		const sf::Drawable& matchAndTransform(const void* hash, const sf::Transformable& transformable) const override;
		void drop( const void* hash ) override;
	private:
		std::unordered_map<const void*, sf::Sprite*> sf_spriteMap;
		std::unique_ptr<ResourceContainerInterface> resourceContainer;

		NullDrawableObject nullDrawableObject;
	};
}

