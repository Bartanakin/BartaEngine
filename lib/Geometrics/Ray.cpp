//
// Created by bartanakin on 11/15/24.
//

#include <Geometrics/Ray.h>

Barta::Ray::Ray(
    Point origin,
    Vector direction
) noexcept:
    origin(origin),
    direction(direction) {}
