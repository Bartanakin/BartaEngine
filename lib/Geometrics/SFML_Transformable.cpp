#include <Geometrics/SFML_Transformable.h>
#include <pch.h>

Barta::SFML_Transformable::SFML_Transformable():
    transformable(std::make_unique<sf::Transformable>()) {}

Barta::SFML_Transformable::SFML_Transformable(
    const SFML_Transformable& second
):
    transformable(std::make_unique<sf::Transformable>(*second.transformable)) {}

Barta::Vector2f Barta::SFML_Transformable::getPosition() const {
    return Vector2f(this->transformable->getPosition());
}

void Barta::SFML_Transformable::setPosition(
    Vector2f position
) {
    this->transformable->setPosition(sf::Vector2f(position.getX(), position.getY()));
}

Barta::Circle Barta::SFML_Transformable::getTransformedCircle(
    const Circle& circle
) const {
    return Circle(
        circle.getRadius(),
        Vector2f(this->transformable->getTransform().transformPoint(circle.getCenter().getX(), circle.getCenter().getY()))
    );
}

void Barta::SFML_Transformable::move(
    Vector2f shift
) {
    this->transformable->move(shift.getX(), shift.getY());
}

Barta::AABB Barta::SFML_Transformable::getTransformedAABB(
    const AABB& aabb
) const {
    if (this->getRotaion() != 0.f) {
        throw std::runtime_error("You can't rotate an AABB object. Consider using an OBB.");
    }

    return AABB(
        Vector2f(this->transformable->getTransform().transformPoint(aabb.getLeftTop().getX(), aabb.getLeftTop().getY())),
        aabb.getWidthHeight()
    );
}

Barta::OBB Barta::SFML_Transformable::getTransformedOBB(
    const OBB& obb
) const {
    return OBB(
        Vector2f(this->transformable->getTransform().transformPoint(obb.getFirstVertex().getX(), obb.getFirstVertex().getY())),
        obb.getWidthHeight(),
        obb.getRotation() + this->getRotaion() * M_PI / 180.f
    );
}

float Barta::SFML_Transformable::getRotaion() const {
    return this->transformable->getRotation();
}

Barta::Vector2f Barta::SFML_Transformable::rotate(
    float rotation,
    Vector2f axis
) {
    axis = axis - this->transformable->getPosition();
    sf::Vector2f sf_axis = {axis.x, axis.y};

    this->transformable->rotate(rotation);

    auto transformAxis = sf::Transform();
    transformAxis.rotate(rotation);
    auto originTranslation = transformAxis.transformPoint(sf_axis);
    this->transformable->move(sf_axis - originTranslation);

    return sf_axis - originTranslation;
}
