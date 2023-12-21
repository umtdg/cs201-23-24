/*
    Author: Umut Dağ
    Student ID: 21801674
    Section No: 2
*/

#pragma once

#include "dyarray.h"

#include <utility>
#include <vector>

template <typename T>
class stack {
    private:
        DynamicArray<T> _c;

    public:
        T& top() { return _c.back(); }
        const T& top() const { return _c.back(); }

        void push(const T& item) { _c.push_back(item); }
        void push(T&& item) { _c.push_back(std::move(item)); }

        void pop() { _c.pop_back(); }

        bool empty() const { return _c.empty(); }
};
