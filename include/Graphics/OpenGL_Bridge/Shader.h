#pragma once
#include <pch.h>

namespace Barta {

// AI generated
class Shader {
    unsigned int ID;
    unsigned int vertex;
    unsigned int fragment;

public:
    Shader(std::string vertexPath, std::string fragmentPath);
    ~Shader();

    unsigned int getID() const noexcept { return ID; }
};

}
