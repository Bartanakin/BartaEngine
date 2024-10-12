#pragma once
#include "../pch.h"

namespace Barta{

	class Vector2f{
	public:
		float x;
		float y;
	    constexpr Vector2f() noexcept = default;
		inline constexpr Vector2f( float x, float y ) : x( x ), y( y ){}
		Vector2f( const Vector2f& second );
		Vector2f( sf::Vector2f vector );
        Barta::Vector2f& operator=(const Barta::Vector2f&);
		inline float getX() const { return this->x; }
		inline float getY() const { return this->y; }

		Vector2f operator*(float scalar) const noexcept;

		float operator*( const Vector2f& ) const;

		constexpr Vector2f operator-() const { return Vector2f(-this->x, -this->y); }

		Vector2f operator-( const Vector2f& ) const;

		Vector2f operator+(const Vector2f&) const;

        Vector2f& operator+=(const Vector2f&);

		bool operator==( const Vector2f& ) const;

		float squareOfDistance(const Vector2f&) const;

		Vector2f perpendicular() const;

		Vector2f normalised() const;

        std::string toString() const noexcept;

        float operator^(const Vector2f) const noexcept;

        static Vector2f zeroise(Vector2f vector, float edge) noexcept;

        friend Vector2f operator*(float, const Vector2f&) noexcept;
	};

    inline Vector2f operator*(float scalar, const Vector2f& vector) noexcept {
        return vector * scalar;
    }

	std::ostream& operator << ( std::ostream&, const Vector2f& );
}
