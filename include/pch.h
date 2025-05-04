#pragma once

#define _USE_MATH_DEFINES

// STL
#include <array>
#include <concepts>
#include <cstring>
#include <exception>
#include <filesystem>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <regex>
#include <sstream>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <vector>

// SFML
#if USE_SFML
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Weffc++"
    #include <SFML/Graphics.hpp>
    #pragma GCC diagnostic pop
#endif

// OpenGL
// clang-format off
#if USE_OPEN_GL
    #include <glad/glad.h>

    #include <GLFW/glfw3.h>
#endif
// clang-format on

// Eigen
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <Eigen/src/Core/Matrix.h>

// other headers
#include <chrono>
#include <math.h>
#include <random>

// DEBUG
#include <iomanip>
#include <stdexcept>

// C++ 20+
#include <concepts>

// json
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
