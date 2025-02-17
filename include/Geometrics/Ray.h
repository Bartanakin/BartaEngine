//
// Created by bartanakin on 11/15/24.
//

#pragma once
#include "Point.h"

namespace Barta {

struct Ray {
    Point origin;
    Vector direction;

    Ray(Point origin, Vector direction) noexcept;
};
}
