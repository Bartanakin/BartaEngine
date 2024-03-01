#include <pch.h>
#include <Geometrics/BartaShapes//Circle.h>

Barta::Circle::Circle( float radius, Vector2f center )
:radius(radius), center(center){}

float Barta::Circle::getRadius() const{
	return this->radius;
}

Barta::Vector2f Barta::Circle::getCenter() const{
	return this->center;
}

bool Barta::Circle::isWithin(Vector2f point) const noexcept {
	return pow(this->radius , 2) >= pow(this->center.getX() - point.getX(), 2)  + pow(this->center.getY() - point.getY(), 2);
}
