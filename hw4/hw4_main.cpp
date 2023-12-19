#include <iostream>

#include "ZooMap.h"

int main() {
    ZooMap zoo_map("cage_file.txt", "zoo_file.txt");

    zoo_map.displayAllCages();
    std::cout << "\n";

    zoo_map.displayAdjacentCages("E");
    std::cout << "\n";

    zoo_map.displayAdjacentCages("C");
    std::cout << "\n";

    zoo_map.displayZooMap();
    std::cout << "\n";

    zoo_map.findSafestPath("E", "A");
    std::cout << "\n";

    zoo_map.findSafestPath("D", "C");
    std::cout << "\n";

    zoo_map.findMostDangerousPath("E", "A");
    std::cout << "\n";

    zoo_map.findMostDangerousPath("D", "C");
    std::cout << "\n";

    zoo_map.findSafestPath("C", "F");
    std::cout << "\n";

    zoo_map.findMostDangerousPath("C", "F");
    std::cout << "\n";

    return 0;
}
