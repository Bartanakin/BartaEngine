#pragma once
#include "../../pch.h"

namespace Barta{

	class NullDrawableObject : public sf::Drawable {
	public:

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
		inline void draw( sf::RenderTarget& renderTarget, sf::RenderStates states ) const override{};
#pragma GCC diagnostic pop
	};

}

