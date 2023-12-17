#pragma once

#include "dyarray.h"
#include "sorted_list.h"

#include <string>


class path {
    private:
        sorted_list<cage> _cages;

    public:
        void add(const cage& c) { _cages.insert(c); }

        const float live_prob() const {
            float prob = 1.0;
            const auto *current = _cages.head();

            while (current != nullptr) {
                prob *= current->value.live_prob();
                current = current->next;
            }

            return prob;
        }
};

class cage {
    private:
        std::string _name;
        float _live_prob;
        sorted_list<std::string> _adjacent_cages;

    public:
        cage(const std::string name, const float live_prob)
            : _name(std::move(name)), _live_prob(live_prob) {}

        void add_adjacent_cage(const std::string& name) {
            _adjacent_cages.insert(name);
        }

        const std::string& name() const { return _name; }
        const float live_prob() const { return _live_prob; }
};
