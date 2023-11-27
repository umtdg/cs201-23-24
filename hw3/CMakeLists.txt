# Create executable target
add_library(smp
    "sorted_list.h"
    "smp_types.h"
    "smp_types.cpp"
    "SocialMediaPlatform.h"
    "SocialMediaPlatform.cpp"
)
target_include_directories(smp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(hw3 "hw3.cpp")
target_link_libraries(hw3 smp)
target_include_directories(hw3 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
