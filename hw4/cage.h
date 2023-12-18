#pragma once

#include "dyarray.h"
#include "sorted_list.h"

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

        void display_adjacent(const std::string& end="\n", bool with_message=false) const {
            if (with_message) std::cout << "The cages adjacent to " << _name << " are:\n";

            std::cout << _name << " -> ";

            _adjacent_cages.display(", ");
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
        DynamicArray<std::string> _cages;
        float _live_prob;

    public:
        path() : _live_prob(1.0f) {}
        path(float live_prob) : _live_prob(live_prob) {}

        bool add(const cage& c) {
            // do not allow circular paths
            if (_cages.find(c.name()) != -1) return false;

            _live_prob *= c.live_prob();

            _cages.add(c.name());

            return true;
        }

        void display() const {
            std::cout << "Path: ";
            _cages.display(" -> ", false, false);
            std::cout << "\n";
            std::cout << "Live probability: " << _live_prob << "\n";
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
