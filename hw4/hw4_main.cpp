#include <iostream>

#include "cage.h"
#include "dyarray.h"

int main() {
    dyarray<cage> a;
    a.push_back(cage("1", 0.0f));
    a.display(",", "\n", false);

    cage& back = a.back();
    a.pop_back();
    a.display(",", "\n", false);

    for (int i = 0; i < 5; i++) {
        a.push_back(cage(std::to_string(i), 0.0f));
    }
    a.display(",", "\n", false);

    dyarray<cage> b(a);
    dyarray<cage> c(std::move(a));
    dyarray<cage> d = b;
    dyarray<cage> e = std::move(b);
}
