cmake_minimum_required(VERSION 3.5)

project(my_project)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Find Boost libraries
find_package(Boost REQUIRED COMPONENTS iostreams)

# Add include directories for Boost and gnuplot-iostream
include_directories(${Boost_INCLUDE_DIRS} /Users/subowen/Desktop/hw/hw/gnuplot-iostream)

# Add executable
add_executable(my_executable main.cpp)

# Link against Boost libraries
target_link_libraries(my_executable ${Boost_L

