#pragma once
#include "../Geometrics/BartaShapes/AABB.h"
#include "../Geometrics/BartaShapes/Circle.h"
#include "BartaShapes/OBB.h"
#include "Vector2f.h"

namespace Barta {
class TransformableInterface {
public:
    TransformableInterface() = default;
    virtual ~TransformableInterface() = default;

    virtual Vector2f getPosition() const = 0;

    virtual void setPosition(Vector2f position) = 0;

    virtual Circle getTransformedCircle(const Circle& circle) const = 0;

    virtual AABB getTransformedAABB(const AABB& aabb) const = 0;

    virtual void move(Vector2f shift) = 0;

    virtual float getRotaion() const = 0;

    virtual void rotate(float, Vector2f) = 0;

    virtual OBB getTransformedOBB(const OBB& aabb) const = 0;
};
}
