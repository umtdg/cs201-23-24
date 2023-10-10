# Create executable target
add_library(hw1
    "dyarray.h"
    "IssueTrackingSystem.h"
    "IssueTrackingSystem.cpp"
)
target_include_directories(hw1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
