# 1. Set the minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.16)

# 2. Name your project and specify the programming language (CXX = C++)
project(AsteroidGame VERSION 2.0 LANGUAGES CXX)

# 3. Tell the compiler to enforce Modern C++17 standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Strict Compiler Warnings and AddressSanitizer for Debug builds
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -fsanitize=address -g)
    add_link_options(-fsanitize=address)
endif()

# 4. Find all .cpp files inside the src/ folder automatically
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 5. Tell CMake to build an executable named "AsteroidsGame" from those sources
add_executable(${PROJECT_NAME} ${SOURCES})

# 6. Allow #include "header.h" to look inside the include/ folder
target_include_directories(${PROJECT_NAME} PRIVATE include)

# 7. Find Raylib installed on your Pop!_OS system and link it to your game
find_package(raylib REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)