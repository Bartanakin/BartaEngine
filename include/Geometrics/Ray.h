//
// Created by bartanakin on 11/15/24.
//

#pragma once
#include "Vector2f.h"

namespace Barta {

struct Ray {
    Vector2f origin;
    Vector2f direction;

    Ray(Vector2f origin, Vector2f direction) noexcept;
};
}
