#pragma once
#include "../pch.h"
#include "TransformableInterface.h"

namespace Barta{

	class SFML_Transformable : public TransformableInterface {
	public:
		SFML_Transformable();
		SFML_Transformable( const SFML_Transformable& second );
		virtual ~SFML_Transformable() noexcept = default;

		Vector2f getPosition() const override;

		void setPosition( Vector2f position ) override;
		
		virtual Circle getTransformedCircle( const Circle& circle ) const override;

		virtual void move( Vector2f shift ) override;

		virtual AABB getTransformedAABB( const AABB& aabb ) const override;

        float getRotaion() const override;

        void rotate(float, Vector2f) override;

	private:
		std::unique_ptr<sf::Transformable> transformable;
	};
}

