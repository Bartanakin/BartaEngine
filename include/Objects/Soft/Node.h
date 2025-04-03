#pragma once
#include <Dynamics/DynamicsDTOCollection.h>
#include <pch.h>

namespace Barta::Objects::Soft {
struct Node {
    std::string label;
    DynamicsDTOCollection dynamicsDTOCollection;
    bool isZeroDirichlet;
};
}
