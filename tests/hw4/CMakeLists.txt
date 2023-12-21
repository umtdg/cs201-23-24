add_executable(test_hw4 "test_hw4.cpp")

if (GCC)
    target_compile_options(test_hw4 PRIVATE -Wno-self-move)
elseif(MSVC)
    target_compile_options(test_hw4 PRIVATE /wd4577)
endif()

target_include_directories(test_hw4 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

configure_file("cage_file.txt" "cage_file.txt" COPYONLY)
configure_file("zoo_file.txt" "zoo_file.txt" COPYONLY)
