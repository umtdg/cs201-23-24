add_executable(test_hw1 "test_hw1.cpp")

if (GCC)
    target_compile_options(test_hw1 PRIVATE -Wno-self-move)
elseif(MSVC)
    target_compile_options(test_hw1 PRIVATE /wd4577)
endif()

target_include_directories(test_hw1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
