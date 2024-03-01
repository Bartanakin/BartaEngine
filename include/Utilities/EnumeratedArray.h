#pragma once
#include "pch.h"

template<typename T>
concept ConvertibleToSize = requires {
    static_cast<size_t>(std::declval<T>());
};

template<ConvertibleToSize E, typename T, size_t N>
class EnumeratedArray : public std::array<T, N>  {
    using Base = std::array<T, N>;
public:
    T& operator[](E case_) noexcept {
        return Base::operator[](static_cast<size_t>(case_));
    }

    const T& operator[](E case_) const noexcept {
        return Base::operator[](static_cast<size_t>(case_));
    }
};
