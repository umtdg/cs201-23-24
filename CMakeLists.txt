cmake_minimum_required(VERSION 3.10)

# Set the project name
project(cs201-23-24)

# Set C++11 as the standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_TESTS "Build the tests" ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "/W4 /WX /EHsc")
    set(CMAKE_CXX_FLAGS_DEBUG "/Od /Zi")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GCC" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fsanitize=address")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG")
endif()

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

# Add hw subdirectories
add_subdirectory(hw1)
add_subdirectory(hw2)
add_subdirectory(hw3)
