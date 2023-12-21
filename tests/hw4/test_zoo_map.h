#include <gtest/gtest.h>

#include <iostream>
#include <fstream>
#include <string>

#include <hw4/ZooMap.h>


TEST(ZooMap, TestInputReading) {
    std::string expected_output = "6 cages and 9 connections have been loaded.\n\n";

    testing::internal::CaptureStdout();

    // --------------------------------------------------------------------
    ZooMap zm("cage_file.txt", "zoo_file.txt");
    std::cout << '\n';
    // --------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expected_output);
}

TEST(ZooMap, TestDisplayMap) {
    const std::string expected_output = "6 cages and 9 connections have been loaded.\n\n"
        "The cages in the zoo are:\n"
        "A, B, C, D, E, F,\n\n"
        "The cages adjacent to E are:\n"
        "E -> D, F,\n\n"
        "The cages adjacent to C are:\n"
        "C ->\n\n"
        "The whole zoo map is:\n"
        "A -> E,\n"
        "B -> A, C, E,\n"
        "C ->\n"
        "D -> A,\n"
        "E -> D, F,\n"
        "F -> B, C,\n\n";

    testing::internal::CaptureStdout();

    // --------------------------------------------------------------------

    ZooMap zm("cage_file.txt", "zoo_file.txt");
    std::cout << '\n';

    zm.displayAllCages();
    std::cout << '\n';

    zm.displayAdjacentCages("E");
    std::cout << '\n';

    zm.displayAdjacentCages("C");
    std::cout << '\n';

    zm.displayZooMap();
    std::cout << '\n';

    // --------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expected_output);
}

TEST(ZooMap, TestZeroOrOnePath_Safest) {
    const std::string expected_output = "6 cages and 9 connections have been loaded.\n\n"
        "No path exists from C to F.\n\n"
        "Safest path from E to D is:\n"
        "E -> D\n"
        "Probability: 0.031500\n\n";

    testing::internal::CaptureStdout();

    // --------------------------------------------------------------------
    ZooMap zm("cage_file.txt", "zoo_file.txt");
    std::cout << '\n';

    zm.findSafestPath("C", "F");
    std::cout << '\n';

    zm.findSafestPath("E", "D");
    std::cout << '\n';
    // --------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expected_output);
}

TEST(ZooMap, TestZeroOrOnePath_MostDangerous) {
    const std::string expected_output = "6 cages and 9 connections have been loaded.\n\n"
        "No path exists from C to F.\n\n"
        "Most dangerous path from E to D is:\n"
        "E -> D\n"
        "Probability: 0.031500\n\n";

    testing::internal::CaptureStdout();

    // --------------------------------------------------------------------
    ZooMap zm("cage_file.txt", "zoo_file.txt");
    std::cout << '\n';

    zm.findMostDangerousPath("C", "F");
    std::cout << '\n';

    zm.findMostDangerousPath("E", "D");
    std::cout << '\n';
    // --------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expected_output);
}

TEST(ZooMap, TestSafestPath) {
    const std::string expected_output = "6 cages and 9 connections have been loaded.\n\n"
        "Safest path from E to A is:\n"
        "E -> F -> B -> A\n"
        "Probability: 0.066825\n\n"
        "Safest path from D to C is:\n"
        "D -> A -> E -> F -> C\n"
        "Probability: 0.003402\n\n";

    testing::internal::CaptureStdout();

    // --------------------------------------------------------------------
    ZooMap zm("cage_file.txt", "zoo_file.txt");
    std::cout << '\n';

    zm.findSafestPath("E", "A");
    std::cout << '\n';

    zm.findSafestPath("D", "C");
    std::cout << '\n';
    // --------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expected_output);
}

TEST(ZooMap, TestMostDangerousPath) {
    const std::string expected_output = "6 cages and 9 connections have been loaded.\n\n"
        "Most dangerous path from E to A is:\n"
        "E -> D -> A\n"
        "Probability: 0.028350\n\n"
        "Most dangerous path from D to C is:\n"
        "D -> A -> E -> F -> B -> C\n"
        "Probability: 0.001123\n\n";

    testing::internal::CaptureStdout();

    // --------------------------------------------------------------------
    ZooMap zm("cage_file.txt", "zoo_file.txt");
    std::cout << '\n';

    zm.findMostDangerousPath("E", "A");
    std::cout << '\n';

    zm.findMostDangerousPath("D", "C");
    std::cout << '\n';
    // --------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expected_output);
}

TEST(ZooMap, ExampleOutput) {
    const std::string expected_output = "6 cages and 9 connections have been loaded.\n\n"
        "The cages in the zoo are:\n"
        "A, B, C, D, E, F,\n\n"
        "The cages adjacent to E are:\n"
        "E -> D, F,\n\n"
        "The cages adjacent to C are:\n"
        "C ->\n\n"
        "The whole zoo map is:\n"
        "A -> E,\n"
        "B -> A, C, E,\n"
        "C ->\n"
        "D -> A,\n"
        "E -> D, F,\n"
        "F -> B, C,\n\n"
        "Safest path from E to A is:\n"
        "E -> F -> B -> A\n"
        "Probability: 0.066825\n\n"
        "Safest path from D to C is:\n"
        "D -> A -> E -> F -> C\n"
        "Probability: 0.003402\n\n"
        "Most dangerous path from E to A is:\n"
        "E -> D -> A\n"
        "Probability: 0.028350\n\n"
        "Most dangerous path from D to C is:\n"
        "D -> A -> E -> F -> B -> C\n"
        "Probability: 0.001123\n\n"
        "No path exists from C to F.\n";

    testing::internal::CaptureStdout();

    // --------------------------------------------------------------------
    ZooMap zm("cage_file.txt", "zoo_file.txt");
    std::cout << '\n';

    zm.displayAllCages();
    std::cout << '\n';

    zm.displayAdjacentCages("E");
    std::cout << '\n';

    zm.displayAdjacentCages("C");
    std::cout << '\n';

    zm.displayZooMap();
    std::cout << '\n';

    zm.findSafestPath("E", "A");
    std::cout << '\n';

    zm.findSafestPath("D", "C");
    std::cout << '\n';

    zm.findMostDangerousPath("E", "A");
    std::cout << '\n';

    zm.findMostDangerousPath("D", "C");
    std::cout << '\n';

    zm.findMostDangerousPath("C", "F");
    // --------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expected_output);
}
