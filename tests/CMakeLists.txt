# googletest
find_package(GTest REQUIRED)

enable_testing()

include_directories(${GTEST_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR})
link_libraries(
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
    pthread
    hw1
)

add_subdirectory(hw1)
