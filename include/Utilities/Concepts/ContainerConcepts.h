#pragma once
#include <pch.h>

namespace Barta::Utilities::Concepts {
template<typename Container, typename T>
concept ConstIteratorContainerConcept = requires(Container c) {
    { std::cbegin(c) } -> std::input_iterator;
    { std::cend(c) } -> std::input_iterator;
    requires std::same_as<std::remove_cvref_t<decltype(*std::cbegin(c))>, T>;
    requires std::same_as<std::remove_cvref_t<decltype(*std::cend(c))>, T>;
};

}
