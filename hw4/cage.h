/*
    Author: Umut Dağ
    Student ID: 21801674
    Section No: 2
*/

#pragma once

#include "dyarray.h"
#include "sorted_list.h"

#include <iomanip>
#include <string>


class cage {
    private:
        std::string _name;
        float _live_prob = 1.0;
        sorted_list<std::string> _adjacent_cages;

    public:
        cage() = default;
        cage(const std::string name, const float live_prob)
            : _name(std::move(name)), _live_prob(live_prob) {}

        void add_adjacent_cage(const std::string& name) {
            _adjacent_cages.insert(name);
        }

        void display_adjacent(const std::string& end, bool with_message) const {
            if (with_message) std::cout << "The cages adjacent to " << _name << " are:\n";

            std::cout << _name << " ->";

            if (!_adjacent_cages.empty()) {
                std::cout << ' ';
                _adjacent_cages.display(", ", ",", false);
            }

            std::cout << end;
        }

        const std::string& name() const { return _name; }
        const float live_prob() const { return _live_prob; }

        sorted_list<std::string>& adjacent_cages() { return _adjacent_cages; }
        const sorted_list<std::string>& adjacent_cages() const { return _adjacent_cages; }

        bool operator<(const cage& other) const { return _name < other._name; }
        bool operator>(const cage& other) const { return _name > other._name; }
        bool operator==(const cage& other) const { return _name == other._name; }
        bool operator!=(const cage& other) const { return _name != other._name; }
        bool operator<=(const cage& other) const { return _name <= other._name; }
        bool operator>=(const cage& other) const { return _name >= other._name; }

        friend std::ostream& operator<<(std::ostream& os, const cage& c) {
            os << c._name;
            return os;
        }
};

class path {
    private:
        dyarray<std::string> _cages;
        float _live_prob;

    public:
        path() : _live_prob(1.0f) {}
        path(float live_prob) : _live_prob(live_prob) {}

        bool add(const cage& c) {
            // do not allow circular paths
            if (_cages.find(c.name()) != -1) return false;

            _live_prob *= c.live_prob();

            _cages.push_back(c.name());

            return true;
        }

        void display() const {
            _cages.display(" -> ", "", false);
            std::cout << "\n";
            std::cout << std::fixed << "Probability: "
                << _live_prob << "\n" << std::defaultfloat;
        }

        bool empty() const {
            return _cages.empty();
        }

        const float live_prob() const { return _live_prob; }

        bool operator<(const path& other) const {
            if (_live_prob == other._live_prob) {
                return _cages.length() > other._cages.length();
            }

            return _live_prob < other._live_prob;
        }
        bool operator>(const path& other) const {
            if (_live_prob == other._live_prob) {
                return _cages.length() < other._cages.length();
            }

            return _live_prob > other._live_prob;
        }
        bool operator==(const path& other) const {
            return _live_prob == other._live_prob
                && _cages.length() == other._cages.length();
        }
        bool operator!=(const path& other) const { return !(*this == other); }
        bool operator<=(const path& other) const { return (*this < other) || (*this == other); }
        bool operator>=(const path& other) const { return (*this > other) || (*this == other); }
};
