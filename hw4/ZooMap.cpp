#include "cage.h"
#include "dyarray.h"
#include "ZooMap.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>

ZooMap::ZooMap(const std::string cageFile, const std::string zooFile) {
    read_cage_file(cageFile);
    read_zoo_file(zooFile);

    std::cout << _cages.length() << " cages and "
            << _num_conns << " connections have been loaded.\n\n";
}

void ZooMap::displayAllCages() const {
    std::cout << "The cages in the zoo are:\n";
    _cages.display(", ");
    std::cout << "\n";
}

void ZooMap::displayAdjacentCages(const std::string cageName) const {
    int index = _cages.find(cage(cageName, 0.0f));
    if (index == -1) {
        std::cout << "Cage " << cageName << " does not exist.\n";
        return;
    }

    _cages[index].display_adjacent("\n", true);
}

void ZooMap::displayZooMap() const {
    std::cout << "The whole zoo map is:\n";
    for (size_t i = 0; i < _cages.length(); i++) {
        _cages[i].display_adjacent();
    }
}

void ZooMap::findSafestPath(const std::string startCage, const std::string endCage) {
    find_path(std::move(startCage), std::move(endCage), true);
}

void ZooMap::findMostDangerousPath(const std::string startCage, const std::string endCage) {
    find_path(std::move(startCage), std::move(endCage), false);
}

// Helpers
void ZooMap::read_cage_file(const std::string& cage_file) {
    std::ifstream cage_stream(cage_file);
    std::string line;

    while (std::getline(cage_stream, line)) {
        std::istringstream iss(line);
        std::string name;
        float live_prob;

        std::getline(iss, name, ';');
        iss >> live_prob;
        _cages.add(cage(name, live_prob));
    }

    cage_stream.close();

    _cages.sort();
}

void ZooMap::read_zoo_file(const std::string& zoo_file) {
    std::ifstream zoo_stream(zoo_file);
    std::string line;

    while (std::getline(zoo_stream, line)) {
        std::istringstream iss(line);
        std::string cage_name;
        std::string adjacent_cage_name;

        std::getline(iss, cage_name, ';');
        std::getline(iss, adjacent_cage_name, ';');

        _cages[_cages.find(cage(cage_name, 0.0f))].add_adjacent_cage(adjacent_cage_name);
        _num_conns++;
    }

    zoo_stream.close();
}

void ZooMap::find_path(const std::string& startCage, const std::string& endCage, bool find_safest) {
    cage& start = _cages[_cages.find(cage(startCage, 0.0f))];
    cage& end = _cages[_cages.find(cage(endCage, 0.0f))];

    // Use a DFS using stack to find all paths from start to end
    // and keep track of the safest path
    path found_path(find_safest ? 0.0f : 1.0f);
    std::stack<std::pair<path, cage>> dfs_stack;

    dfs_stack.push({path{}, start});

    while(!dfs_stack.empty()) {
        auto dfs_top = dfs_stack.top();
        path p = dfs_top.first;
        cage c = dfs_top.second;

        dfs_stack.pop();

        // Try to add cage to path, skip if cage is already in path
        if (!p.add(c)) continue;

        // If we reached the end, add path to paths
        if (c == end) {
            if (find_safest ? p > found_path : p < found_path) {
                found_path = p;
            }
            continue;
        }

        // Add all adjacent cages to stack
        const auto* adj = c.adjacent_cages().head();
        while (adj != nullptr) {
            dfs_stack.push({p, _cages[_cages.find(cage(adj->value, 0.0f))]});
            adj = adj->next;
        }
    }

    // If the found path is empty, no path exists
    if (found_path.empty()) {
        std::cout << "No path exists from " << startCage
                << " to " << endCage << ".\n";
    } else {
        std::cout << (find_safest ? "Safest" : "Most dangerous")
                << " path from " << startCage << " to " << endCage
                << " is:\n";
        found_path.display();
    }
}
