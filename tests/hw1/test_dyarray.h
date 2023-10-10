#include <hw1/dyarray.h>
#include <hw1/IssueTrackingSystem.h>

#include <gtest/gtest.h>

class CopyableMovable {
    public:
        int x;
        bool copyConstructed;
        bool moveConstructed;

        CopyableMovable() : x(0), copyConstructed(false), moveConstructed(false) {}
        CopyableMovable(int x) : x(x), copyConstructed(false), moveConstructed(false) {}
        CopyableMovable(const CopyableMovable& other) : x(other.x), copyConstructed(true), moveConstructed(false) {}
        CopyableMovable(CopyableMovable&& other) noexcept : x(other.x), copyConstructed(false), moveConstructed(true) {}

        CopyableMovable& operator=(const CopyableMovable& other) {
            if (this == &other) return *this;

            x = other.x;
            copyConstructed = true;
            moveConstructed = false;

            return *this;
        }
        CopyableMovable& operator=(CopyableMovable&& other) noexcept {
            if (this == &other) return *this;

            x = other.x;
            copyConstructed = false;
            moveConstructed = true;

            return *this;
        }
};

class Copyable {
    public:
    int x;
    bool copyConstructed;

    Copyable() : x(0), copyConstructed(false) {}
    Copyable(int x) : x(x), copyConstructed(false) {}
    Copyable(const Copyable& other) : x(other.x), copyConstructed(true) {}
    Copyable& operator=(const Copyable& other) {
        if (this == &other) return *this;

        x = other.x;
        copyConstructed = true;
        return *this;
    }

    Copyable(Copyable&& other) = delete;
    Copyable& operator=(Copyable&& other) = delete;
};

class Movable {
    public:
    int x;
    bool moveConstructed;

    Movable() : x(0), moveConstructed(false) {}
    Movable(int x) : x(x), moveConstructed(false) {}

    Movable(Movable&& other) : x(other.x), moveConstructed(true) {}
    Movable& operator=(Movable&& other) {
        x = other.x;
        moveConstructed = true;

        return *this;
    }

    Movable(const Movable& other) = delete;
    Movable& operator=(const Movable& other) = delete;
};


TEST(DynamicArray, Construct) {
    DynamicArray<int> arr;
    EXPECT_NE(arr.data(), nullptr);
    EXPECT_EQ(arr.length(), 0);
    EXPECT_EQ(arr.capacity(), 0);
}

TEST(DynamicArray, ReserveWithoutData) {
    DynamicArray<int> arr;
    arr.reserve(2);

    EXPECT_NE(arr.data(), nullptr);
    EXPECT_EQ(arr.length(), 0);
    EXPECT_EQ(arr.capacity(), 2);
}

TEST(DynamicArray, ReserveLess) {
    DynamicArray<int> arr;
    arr.reserve(2);
    arr.reserve(1);

    EXPECT_NE(arr.data(), nullptr);
    EXPECT_EQ(arr.length(), 0);
    EXPECT_EQ(arr.capacity(), 2);
}

TEST(DynamicArray, ReserveWithData) {
    DynamicArray<int> arr;
    arr.reserve(2);
    arr.add(1);
    arr.add(2);

    arr.reserve(4);

    EXPECT_NE(arr.data(), nullptr);
    EXPECT_EQ(arr.length(), 2);
    EXPECT_EQ(arr.capacity(), 4);
}

TEST(DynamicArray, AddToEmpty) {
    DynamicArray<int> arr;
    arr.add(1);

    EXPECT_NE(arr.data(), nullptr);
    EXPECT_EQ(arr.length(), 1);
    EXPECT_EQ(arr.capacity(), 1);
    EXPECT_EQ(arr.at(0), 1);
}

TEST(DynamicArray, AddToNonEmpty) {
    DynamicArray<int> arr;
    arr.reserve(2);
    arr.add(1);
    arr.add(2);
    arr.add(3);

    EXPECT_NE(arr.data(), nullptr);
    EXPECT_EQ(arr.length(), 3);
    EXPECT_EQ(arr.capacity(), 4);
    EXPECT_EQ(arr.at(0), 1);
    EXPECT_EQ(arr.at(1), 2);
    EXPECT_EQ(arr.at(2), 3);

    arr.add(4);
    arr.add(5);

    EXPECT_NE(arr.data(), nullptr);
    EXPECT_EQ(arr.length(), 5);
    EXPECT_EQ(arr.capacity(), 8);
    EXPECT_EQ(arr.at(0), 1);
    EXPECT_EQ(arr.at(1), 2);
    EXPECT_EQ(arr.at(2), 3);
    EXPECT_EQ(arr.at(3), 4);
    EXPECT_EQ(arr.at(4), 5);
}

TEST(DynamicArray, AddCopyableMovable) {
    DynamicArray<CopyableMovable> arr;
    arr.reserve(2);

    // add copyable & movable rvalue
    arr.add(CopyableMovable(1));

    // add copyable & movable lvalue
    CopyableMovable cm1(4);
    arr.add(cm1);

    EXPECT_NE(arr.data(), nullptr);
    EXPECT_EQ(arr.length(), 2);
    EXPECT_EQ(arr.capacity(), 2);

    EXPECT_EQ(arr.at(0).x, 1);
    EXPECT_EQ(arr.at(0).copyConstructed, false);
    EXPECT_EQ(arr.at(0).moveConstructed, true);

    EXPECT_EQ(arr.at(1).x, 4);
    EXPECT_EQ(arr.at(1).copyConstructed, true);
    EXPECT_EQ(arr.at(1).moveConstructed, false);
}

TEST(DynamicArray, AddCopyable) {
    DynamicArray<Copyable> arr;
    arr.reserve(2);

    // add copyable rvalue - should not compile
    // arr.add(Copyable(1));

    // add copyable lvalue
    Copyable c1(4);
    arr.add(c1);

    EXPECT_NE(arr.data(), nullptr);
    EXPECT_EQ(arr.length(), 1);
    EXPECT_EQ(arr.capacity(), 2);

    EXPECT_EQ(arr.at(0).x, 4);
    EXPECT_EQ(arr.at(0).copyConstructed, true);
}

TEST(DynamicArray, AddMovable) {
    DynamicArray<Movable> arr;
    arr.reserve(2);

    // add movable rvalue
    arr.add(Movable(1));

    // add movable lvalue - should not compile
    // Movable m1(4);
    // arr.add(m1);

    EXPECT_NE(arr.data(), nullptr);
    EXPECT_EQ(arr.length(), 1);
    EXPECT_EQ(arr.capacity(), 2);

    EXPECT_EQ(arr.at(0).x, 1);
    EXPECT_EQ(arr.at(0).moveConstructed, true);
}

TEST(DynamicArray, CopyConstruct) {
    DynamicArray<int> arr;
    arr.reserve(2);
    arr.add(1);
    arr.add(2);

    int *arrData = arr.data();

    DynamicArray<int> arrCopy(arr);
    EXPECT_NE(arrCopy.data(), nullptr);
    EXPECT_NE(arrCopy.data(), arr.data());
    EXPECT_EQ(arrCopy.length(), 2);
    EXPECT_EQ(arrCopy.capacity(), 2);
    EXPECT_EQ(arrCopy.at(0), 1);
    EXPECT_EQ(arrCopy.at(1), 2);

    EXPECT_EQ(arr.data(), arrData);
    EXPECT_EQ(arr.length(), 2);
    EXPECT_EQ(arr.capacity(), 2);
    EXPECT_EQ(arr.at(0), 1);
    EXPECT_EQ(arr.at(1), 2);
}

TEST(DynamicArray, MoveConstruct) {
    DynamicArray<int> arr;
    arr.reserve(2);
    arr.add(1);
    arr.add(2);

    int *arrData = arr.data();

    DynamicArray<int> arrMove(std::move(arr));
    EXPECT_EQ(arr.data(), nullptr);
    EXPECT_EQ(arr.length(), 0);
    EXPECT_EQ(arr.capacity(), 0);

    EXPECT_NE(arrMove.data(), nullptr);
    EXPECT_EQ(arrMove.data(), arrData);
    EXPECT_EQ(arrMove.length(), 2);
    EXPECT_EQ(arrMove.capacity(), 2);
    EXPECT_EQ(arrMove.at(0), 1);
    EXPECT_EQ(arrMove.at(1), 2);
}

TEST(DynamicArray, CopyAssignEmpty) {
    DynamicArray<int> arr;
    arr.reserve(2);
    arr.add(1);
    arr.add(2);

    DynamicArray<int> arrCopy;

    int *arrData = arr.data();

    arrCopy = arr;
    EXPECT_NE(arrCopy.data(), nullptr);
    EXPECT_NE(arrCopy.data(), arr.data());
    EXPECT_EQ(arrCopy.length(), 2);
    EXPECT_EQ(arrCopy.capacity(), 2);
    EXPECT_EQ(arrCopy.at(0), 1);
    EXPECT_EQ(arrCopy.at(1), 2);

    EXPECT_EQ(arr.data(), arrData);
    EXPECT_EQ(arr.length(), 2);
    EXPECT_EQ(arr.capacity(), 2);
    EXPECT_EQ(arr.at(0), 1);
    EXPECT_EQ(arr.at(1), 2);
}

TEST(DynamicArray, CopyAssignNonEmpty) {
    DynamicArray<int> arr;
    arr.reserve(2);
    arr.add(1);
    arr.add(2);

    DynamicArray<int> arrCopy;
    arrCopy.reserve(3);
    arrCopy.add(3);
    arrCopy.add(4);
    arrCopy.add(5);

    int *arrData = arr.data();

    arrCopy = arr;

    EXPECT_NE(arrCopy.data(), nullptr);
    EXPECT_NE(arrCopy.data(), arr.data());
    EXPECT_EQ(arrCopy.length(), 2);
    EXPECT_EQ(arrCopy.capacity(), 2);
    EXPECT_EQ(arrCopy.at(0), 1);
    EXPECT_EQ(arrCopy.at(1), 2);

    EXPECT_EQ(arr.data(), arrData);
    EXPECT_EQ(arr.length(), 2);
    EXPECT_EQ(arr.capacity(), 2);
    EXPECT_EQ(arr.at(0), 1);
    EXPECT_EQ(arr.at(1), 2);
}

TEST(DynamicArray, MoveAssignEmpty) {
    DynamicArray<int> arr;
    arr.reserve(2);
    arr.add(1);
    arr.add(2);

    DynamicArray<int> arrMove;

    int *arrData = arr.data();

    arrMove = std::move(arr);

    EXPECT_EQ(arr.data(), nullptr);
    EXPECT_EQ(arr.length(), 0);
    EXPECT_EQ(arr.capacity(), 0);

    EXPECT_NE(arrMove.data(), nullptr);
    EXPECT_EQ(arrMove.data(), arrData);
    EXPECT_EQ(arrMove.length(), 2);
    EXPECT_EQ(arrMove.capacity(), 2);
    EXPECT_EQ(arrMove.at(0), 1);
    EXPECT_EQ(arrMove.at(1), 2);
}

TEST(DynamicArray, MoveAssignNonEmpty) {
    DynamicArray<int> arr;
    arr.reserve(2);
    arr.add(1);
    arr.add(2);

    DynamicArray<int> arrMove;
    arrMove.reserve(3);
    arrMove.add(3);
    arrMove.add(4);
    arrMove.add(5);

    int *arrData = arr.data();

    arrMove = std::move(arr);

    EXPECT_EQ(arr.data(), nullptr);
    EXPECT_EQ(arr.length(), 0);
    EXPECT_EQ(arr.capacity(), 0);

    EXPECT_NE(arrMove.data(), nullptr);
    EXPECT_EQ(arrMove.data(), arrData);
    EXPECT_EQ(arrMove.length(), 2);
    EXPECT_EQ(arrMove.capacity(), 2);
    EXPECT_EQ(arrMove.at(0), 1);
    EXPECT_EQ(arrMove.at(1), 2);
}

TEST(DynamicArray, CopyAssignSelf) {
    DynamicArray<int> arr;
    arr.reserve(2);
    arr.add(1);
    arr.add(2);

    int *arrData = arr.data();

    arr = arr;

    EXPECT_NE(arr.data(), nullptr);
    EXPECT_EQ(arr.data(), arrData);
    EXPECT_EQ(arr.length(), 2);
    EXPECT_EQ(arr.capacity(), 2);
    EXPECT_EQ(arr.at(0), 1);
    EXPECT_EQ(arr.at(1), 2);
}

TEST(DynamicArray, MoveAssignSelf) {
    DynamicArray<int> arr;
    arr.reserve(2);
    arr.add(1);
    arr.add(2);

    int *arrData = arr.data();

    arr = std::move(arr);

    EXPECT_NE(arr.data(), nullptr);
    EXPECT_EQ(arr.data(), arrData);
    EXPECT_EQ(arr.length(), 2);
    EXPECT_EQ(arr.capacity(), 2);
    EXPECT_EQ(arr.at(0), 1);
    EXPECT_EQ(arr.at(1), 2);
}

TEST(DynamicArray, Remove) {
    DynamicArray<int> arr;
    arr.reserve(5);
    arr.add(1);
    arr.add(2);
    arr.add(3);
    arr.add(4);
    arr.add(5);

    int *data = arr.data();

    arr.remove(0);

    EXPECT_EQ(arr.data(), data);
    EXPECT_EQ(arr.length(), 4);
    EXPECT_EQ(arr.capacity(), 5);
    EXPECT_EQ(arr.at(0), 2);
    EXPECT_EQ(arr.at(1), 3);
    EXPECT_EQ(arr.at(2), 4);
    EXPECT_EQ(arr.at(3), 5);

    EXPECT_THROW(arr.remove(4), std::out_of_range);
    arr.remove(3);

    EXPECT_EQ(arr.data(), data);
    EXPECT_EQ(arr.length(), 3);
    EXPECT_EQ(arr.capacity(), 5);
    EXPECT_EQ(arr.at(0), 2);
    EXPECT_EQ(arr.at(1), 3);
    EXPECT_EQ(arr.at(2), 4);

    arr.remove(1);

    EXPECT_EQ(arr.data(), data);
    EXPECT_EQ(arr.length(), 2);
    EXPECT_EQ(arr.capacity(), 5);
    EXPECT_EQ(arr.at(0), 2);
    EXPECT_EQ(arr.at(1), 4);
}
