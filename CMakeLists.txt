# Minimum CMake version required
cmake_minimum_required(VERSION 3.15)

# Project name and language
project(sysMonitor LANGUAGES CXX)

# Equivalent to -std=c++17 in your CXXFLAGS
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Equivalent to your $(wildcard src/*.cpp)
file(GLOB SRCS src/*.cpp)

# Equivalent to your $(TARGET) = monitor
add_executable(monitor ${SRCS})

# Equivalent to -I include in your CXXFLAGS
target_include_directories(monitor PRIVATE include)

# Equivalent to -Wall -Wextra in your CXXFLAGS
target_compile_options(monitor PRIVATE -Wall -Wextra)