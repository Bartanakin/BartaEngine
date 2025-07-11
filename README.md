# **BartaEngine**

_This is a c++ library which implements core features of a physics engine. The core concepts for now are:_ 
* _events handling system_
* _velocity calculation_
* _collision detection and collision responses_

_The project is open to collaboration at my GitHub account as there are plenty of ideas for new functionalities. This program is a base for my Master's degree research about soft bodies simulation._

## **Table of Contents**

1. [Installation](#installation)
2. [Development](#development)
3. [Examples](#examples)
---

## **Installation**

### **Prerequisites**
- **C++20 Compiler**: Ensure you have a compiler that supports C++20 (e.g., GCC 10+, Clang 10+, or MSVC 2019+).
- **CMake**: Required for building the project. Install the latest version from [CMake](https://cmake.org/download/).
- **SFML 2.6.x**: The project depends on [SFML](https://www.sfml-dev.org/) version 2.6.x.

### **Option 1: Use the library directly via `FetchContent`**
* Add the following to your `CMakeLists.txt` file:
   ```cmake
   include(FetchContent)

   FetchContent_Declare(
       BartaEngine
       GIT_REPOSITORY https://github.com/Bartanakin/BartaEngine.git
       GIT_TAG        main
   )

   FetchContent_MakeAvailable(BartaEngine)

   target_link_libraries(target PRIVATE BartaEngine)

### **Option 2: Use an existing template repository* (recommended)*
1. Clone the template repository
   ```bash
    git clone https://github.com/Bartanakin/BartaEngineSandbox.git

2. Proceed if you want to develop BartaEngine as well
3. Clone this repository
   ```bash
    git clone https://github.com/Bartanakin/BartaEngine.git
4. In *BartaEngineSandbox* in `CMakeListst.txt` in the root directory change FetchContent_Declare:
   ```cmake
   FetchContent_Declare(
       BartaEngine
       SOURCE_DIR /local/path/to/BartaEngine
   )

## Development

* To ensure your pull request passes the GitHub Actions checks, I recommend using **clang-format 19** for code formatting. As for 20-11-2024 it is still unofficial version that you can download from [here](https://releases.llvm.org/).
* All the current issues are at the [Issues section](https://github.com/Bartanakin/BartaEngine/issues).
* You can join the development community: write to me on [Discord #Bartanakin](https://discord.com/)  or email me `Bartanakin.bak@student.uj.edu.pl`

## Examples
### 1. Static simulation of a soft body
We import mesh of a pyramid consisting of 10 nodes where 5 of them are in the base of the shape. The base is constrained by the Dirichlet condition, namely we set the displacement to 0 in advance. On the topmost node there is a force applied in the `x` direction given by the formula:
$$
    f_{\text{ext},x_0}(t) = 300(t - 3) \text{ for } t \in [0,3]
$$
where $t$ is the time of the simulation.
The rest of the nodes are unconstrained.
![sim1](examples/sim1.gif)

### 2. Dynamic simulation of a soft body
We import mesh of a pyramid consisting of 10 nodes where 5 of them are in the base of the shape. The base is constrained by the Dirichlet condition, namely we set the displacement to 0 in advance. On the topmost node there is a force applied in the `x` direction given by the formula:
$$
f_{\text{ext},x_0}(t) = \begin{cases}
    -100 &\text{ for } t \in [0,3]\\
    0 &\text{ for } t \in (3, 6]
\end{cases}
$$
where $t$ is the time of the simulation.
The rest of the nodes are unconstrained.
![sim2](examples/sim2.gif)