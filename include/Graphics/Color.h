#pragma once
#include <pch.h>

namespace Barta {

struct HSL {
    float hue;
    float saturation;
    float lightness;
};

struct Color {
    constexpr Color() noexcept = default;

    /// Constructor using RGB values
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

    /// Constructor using HEX values with hex format 0xRRGGBB
    constexpr explicit Color(
        unsigned int hex,
        unsigned char a = 255
    ) noexcept:
        r((hex >> 16) & 0xFF),
        g((hex >> 8) & 0xFF),
        b(hex & 0xFF),
        a(a) {}

    /// Constructor using HEX values with hex format #RRGGBB
    explicit Color(
        const std::string& hex,
        unsigned char a = 255
    ):
        Color(std::stoul(hex.substr(1), nullptr, 16), a) {
        // if (hex[0] != '#' || hex.size() != 7) {
        //     throw std::invalid_argument("Invalid hex format");
        // }
    }

    /// Constructor using HSL values
    /// @param hsl HSL struct with hue, saturation and lightness values
    /// @param a Alpha value (0-255)
    explicit Color(
        HSL hsl,
        unsigned char a = 255
    ) noexcept:
        a(a) {
        // Checking if the values are in the correct range
        // if (hsl.saturation < 0.0f || hsl.saturation > 1.0f) {
        //     throw std::invalid_argument("Saturation must be in the range [0, 1]");
        // }
        //
        // if (hsl.lightness < 0.0f || hsl.lightness > 1.0f) {
        //     throw std::invalid_argument("Lightness must be in the range [0, 1]");
        // }

        hsl.hue = std::fmod(hsl.hue, 360.0f);

        const float chroma = (1.0f - std::abs(2.0f * hsl.lightness - 1.0f)) * hsl.saturation;
        const float huePrime = static_cast<float>(hsl.hue) / 60.0f;
        const float x = chroma * (1.0f - std::abs(std::fmod(huePrime, 2.0f) - 1.0f));
        const float m = hsl.lightness - chroma / 2.0f;

        float r_temp, g_temp, b_temp;

        if (huePrime < 1.0f) {
            r_temp = chroma;
            g_temp = x;
            b_temp = 0.0f;
        } else if (huePrime < 2.0f) {
            r_temp = x;
            g_temp = chroma;
            b_temp = 0.0f;
        } else if (huePrime < 3.0f) {
            r_temp = 0.0f;
            g_temp = chroma;
            b_temp = x;
        } else if (huePrime < 4.0f) {
            r_temp = 0.0f;
            g_temp = x;
            b_temp = chroma;
        } else if (huePrime < 5.0f) {
            r_temp = x;
            g_temp = 0.0f;
            b_temp = chroma;
        } else {
            r_temp = chroma;
            g_temp = 0.0f;
            b_temp = x;
        }

        this->r = static_cast<unsigned char>(std::round((r_temp + m) * 255.0f));
        this->g = static_cast<unsigned char>(std::round((g_temp + m) * 255.0f));
        this->b = static_cast<unsigned char>(std::round((b_temp + m) * 255.0f));
    }

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
