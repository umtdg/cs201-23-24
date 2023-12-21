#include <iostream>
#include <stack>
#include <vector>

#include "stack.h"
#include "ZooMap.h"


int main() {
    ZooMap zm("cage_file.txt", "zoo_file.txt");
    std::cout << '\n';

    zm.findSafestPath("E", "D");
}
