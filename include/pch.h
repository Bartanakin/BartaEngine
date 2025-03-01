#pragma once

// STL
#include <array>
#include <concepts>
#include <exception>
#include <filesystem>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <vector>

// SFML
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <SFML/Graphics.hpp>
#pragma GCC diagnostic pop

#define _USE_MATH_DEFINES

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
