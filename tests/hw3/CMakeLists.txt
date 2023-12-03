add_executable(test_hw3 "test_hw3.cpp")

if (GCC)
    target_compile_options(test_hw3 PRIVATE -Wno-self-move)
elseif(MSVC)
    target_compile_options(test_hw3 PRIVATE /wd4577)
endif()

target_include_directories(test_hw3 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
