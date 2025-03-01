#pragma once
#include <pch.h>

namespace Barta {
struct Color {
    constexpr Color() noexcept = default;

    constexpr Color(
        unsigned char r,
        unsigned char g,
        unsigned char b,
        unsigned char a = 255
    ) noexcept:
        r(r),
        g(g),
        b(b),
        a(a) {}

    ~Color() noexcept = default;

    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

inline void from_json(
    const json& j,
    Color& c
) noexcept {
    j.at("r").get_to(c.r);
    j.at("g").get_to(c.g);
    j.at("b").get_to(c.b);
    if (j.contains("a")) {
        j.at("a").get_to(c.a);
    } else {
        c.a = 255;
    }
}
}
