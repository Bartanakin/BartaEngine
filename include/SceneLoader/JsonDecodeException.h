#pragma once
#include <pch.h>

namespace Barta::SceneLoader {

class JsonDecodeException: public std::exception {
public:
    explicit JsonDecodeException(
        std::string err
    ) noexcept:
        err("JSON DECODE ERROR" + std::move(err)) {}

    const char* what() const noexcept override { return this->err.c_str(); }

private:
    std::string err;
};

}
