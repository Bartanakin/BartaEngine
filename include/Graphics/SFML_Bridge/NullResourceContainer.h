#pragma once
#include "pch.h"
#include "ResourceContainerInterface.h"

namespace Barta{

    class NullResourceContainer : public ResourceContainerInterface{
    public:
        NullResourceContainer() = default;
        virtual ~NullResourceContainer() = default;
        NullResourceContainer( const NullResourceContainer& ) = delete;

        virtual bool hasTexture( const int resource ) const { return false; };

        virtual const sf::Texture& getTexture( const int resource ) const { throw "No textures"; };

        virtual const sf::IntRect getTextureRect( const int resource ) const { return sf::IntRect(); };
    };
}
