#pragma once

namespace Barta{
    struct Color {
    public:
        constexpr Color() noexcept = default;
        constexpr Color(
            unsigned char r,
            unsigned char g,
            unsigned char b,
            unsigned char a = 255
        ) noexcept :
            r(r),
            g(g),
            b(b),
            a(a)
        {}
        ~Color() noexcept = default;
        
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };
}

