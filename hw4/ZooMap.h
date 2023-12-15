#pragma once

#include <string>

class ZooMap {
    public:
        ZooMap(const std::string cageFile, const std::string zooFile);
        ~ZooMap();

        void displayAllCages() const;
        void displayAdjacentCages(const std::string cageName) const;
        void displayZooMap() const;

        void findSafestPath(const std::string startCage, const std::string endCage);
        void findMostDangerousPath(const std::string startCage, const std::string endCage);
};
