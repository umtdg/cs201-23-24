cmake_minimum_required(VERSION 3.10)

# Set the project name
project(cs201-23-24)

# Set C++11 as the standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_TESTS "Build the tests" ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG")

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()


# Add the hw1 subdirectory
add_subdirectory(hw1)
