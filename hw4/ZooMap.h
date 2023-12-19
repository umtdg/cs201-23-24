#pragma once

#include "cage.h"
#include "dyarray.h"

#include <string>

class ZooMap {
    private:
        DynamicArray<cage> _cages;
        size_t _num_conns = 0;

        void read_cage_file(const std::string& cage_file);
        void read_zoo_file(const std::string& zoo_file);

        void find_path(
            const std::string& startCage,
            const std::string& endCage,
            bool find_safest=true
        );

    public:
        ZooMap(const std::string cageFile, const std::string zooFile);
        ~ZooMap() = default;

        // Rule of five
        ZooMap(const ZooMap& other) = default;
        ZooMap(ZooMap&& other) noexcept = default;

        ZooMap& operator=(const ZooMap& other) = default;
        ZooMap& operator=(ZooMap&& other) noexcept = default;

        void displayAllCages() const;
        void displayAdjacentCages(const std::string cageName) const;
        void displayZooMap() const;

        void findSafestPath(const std::string startCage, const std::string endCage);
        void findMostDangerousPath(const std::string startCage, const std::string endCage);
};
