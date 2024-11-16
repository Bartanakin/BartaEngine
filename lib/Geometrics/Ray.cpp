//
// Created by bartanakin on 11/15/24.
//

#include "Geometrics/Ray.h"

Barta::Ray::Ray(
    Vector2f origin,
    Vector2f direction
) noexcept:
    origin(origin),
    direction(direction) {}
