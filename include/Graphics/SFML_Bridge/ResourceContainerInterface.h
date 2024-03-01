#pragma once
#include "../../pch.h"

namespace Barta{

	class ResourceContainerInterface{
	public:
		ResourceContainerInterface() = default;
		virtual ~ResourceContainerInterface() = default;
		ResourceContainerInterface( const ResourceContainerInterface& ) = delete;

		virtual bool hasTexture( const int resource ) const = 0;

		virtual const sf::Texture& getTexture( const int resource ) const = 0;

		virtual const sf::IntRect getTextureRect( const int resource ) const = 0;
	};
}
