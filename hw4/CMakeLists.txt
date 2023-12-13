# Create executable target
add_library(hw4
    "ZooMap.h"
    "ZooMap.cpp"
)
target_include_directories(hw4 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(hw4_main "hw4_main.cpp")
target_link_libraries(hw4_main hw4)
target_include_directories(hw4_main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
