/*
    Author: Umut Dağ
    Student ID: 21801674
    Section No: 2
*/

#pragma once

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

template <typename T>
class DynamicArray {
    protected:
        T *buffer;
        size_t _capacity;
        size_t _length;
        size_t _growthRate;
        bool _shrinkOnRemove;

    public:
        DynamicArray(size_t growthRate = 0, bool shrinkOnRemove = false)
            : buffer(new T[0]), _capacity(0), _length(0),
            _growthRate(growthRate), _shrinkOnRemove(shrinkOnRemove)
        {}
        ~DynamicArray() {
            if (buffer) {
                delete[] buffer;
                buffer = nullptr;
            }
            _capacity = 0;
            _length = 0;
            _growthRate = 0;
            _shrinkOnRemove = false;
        }

        DynamicArray(const DynamicArray& other) {
            _capacity = other._capacity;
            _length = other._length;
            _growthRate = other._growthRate;
            _shrinkOnRemove = other._shrinkOnRemove;

            buffer = new T[_capacity];
            for (size_t i = 0; i < _length; i++) {
                buffer[i] = other.buffer[i];
            }
        }
        DynamicArray(DynamicArray&& other) noexcept
            : buffer(std::exchange(other.buffer, nullptr)),
                _capacity(std::exchange(other._capacity, 0)),
                _length(std::exchange(other._length, 0)),
                _growthRate(std::exchange(other._growthRate, 0)),
                _shrinkOnRemove(std::exchange(other._shrinkOnRemove, false))
        {}

        DynamicArray& operator=(const DynamicArray& other) {
            if (this == &other) return *this;

            return *this = DynamicArray(other);
        }
        DynamicArray& operator=(DynamicArray&& other) noexcept {
            if (this == &other) return *this;

            _capacity = std::exchange(other._capacity, 0);
            _length = std::exchange(other._length, 0);
            _growthRate = std::exchange(other._growthRate, 0);
            _shrinkOnRemove = std::exchange(other._shrinkOnRemove, false);

            if (buffer) delete[] buffer;
            buffer = std::exchange(other.buffer, nullptr);

            return *this;
        }

        void reserve(size_t newCap) {
            if (newCap <= _capacity) return;

            T *newBuffer = new T[newCap];
#if __cplusplus == 201103L || __cplusplus == 201402L
            reserve_helper(newBuffer, std::is_copy_constructible<T>());
#elif __cplusplus >= 201703L
            if constexpr (std::is_copy_constructible_v<T>) {
                for (size_t i = 0; i < _length; i++) {
                    newBuffer[i] = buffer[i];
                }
            } else {
                for (size_t i = 0; i < _length; i++) {
                    newBuffer[i] = std::move(buffer[i]);
                }
            }
#endif

            delete[] buffer;
            buffer = newBuffer;
            _capacity = newCap;
        }

        void shrink_to_fit() {
            if (_length == _capacity) return;

            T *newBuffer = new T[_length];

#if __cplusplus == 201103L || __cplusplus == 201402L
            reserve_helper(newBuffer, std::is_copy_constructible<T>());
#elif __cplusplus >= 201703L
            if constexpr (std::is_copy_constructible_v<T>) {
                for (size_t i = 0; i < _length; i++) {
                    newBuffer[i] = buffer[i];
                }
            } else {
                for (size_t i = 0; i < _length; i++) {
                    newBuffer[i] = std::move(buffer[i]);
                }
            }
#endif

            delete[] buffer;
            buffer = newBuffer;
            _capacity = _length;
        }

        // expand if there is no space left
        void expand() {
            if (_length < _capacity) return;

            if (_growthRate > 0) reserve(_capacity + _growthRate);
            else reserve(_capacity == 0 ? 1 : _capacity * 2);
        }

        void push_back(const T& value) {
            expand();

            buffer[_length++] = value;
        }

        void push_back(T&& value) {
            expand();

            buffer[_length++] = std::move(value);
        }

        void remove(size_t index) {
            if (index >= _length) throw std::out_of_range("Index out of range");

            // destruct the item to avoid memory leaks
            // the container already requires the type to be destructible and
            // default constructible
            buffer[index].~T();
            buffer[index] = std::move(T());

            // remove the item
            for (size_t i = index; i < _length - 1; i++) {
                buffer[i] = buffer[i + 1];
            }

            _length--;

            if (_shrinkOnRemove) shrink_to_fit();
        }

        void pop_back() { remove(_length - 1); }

        T& at(size_t index) { return this[index]; }
        const T& at(size_t index) const { return this[index]; }

        T& operator[](size_t index) {
            if (index >= _length) throw std::out_of_range("Index out of range");

            return buffer[index];
        }
        const T& operator[](size_t index) const {
            if (index >= _length) throw std::out_of_range("Index out of range");

            return buffer[index];
        }

        T& front() { return buffer[0]; }
        const T& front() const { return buffer[0]; }

        T& back() { return buffer[_length - 1]; }
        const T& back() const { return buffer[_length - 1]; }

        int find(const T& value) const {
            for (size_t i = 0; i < _length; i++) {
                if (buffer[i] == value) return i;
            }

            return -1;
        }

        void sort() {
            bool swapped;
            size_t n = _length;
            do {
                swapped = false;
                for (size_t i = 1; i < n; i++) {
                    if (buffer[i - 1] > buffer[i]) {
                        // Swap the elements
                        std::swap(buffer[i - 1], buffer[i]);
                        swapped = true;
                    }
                }
                n--; // Reduce the range of unsorted elements
            } while (swapped);
        }

        size_t length() const noexcept { return _length; }
        size_t capacity() const noexcept { return _capacity; }

        T* data() noexcept { return buffer; }
        const T* data() const noexcept { return buffer; }

        bool empty() const {
            return _length == 0;
        }

        void
        display(const std::string& delim,
            const std::string& end,
            bool print_none_if_empty
        ) const {
            if (_length == 0 && print_none_if_empty) {
                std::cout << "None\n";
                return;
            }

            for (size_t i = 0; i < _length; i++) {
                std::cout << buffer[i];
                if (i != _length - 1) std::cout << delim;
            }

            std::cout << end;
        }

    private:
#if __cplusplus == 201103L || __cplusplus == 201402L
        void reserve_helper(T *newBuffer, std::false_type) {
            for (size_t i = 0; i < _length; i++) {
                newBuffer[i] = std::move(buffer[i]);
            }
        }

        void reserve_helper(T *newBuffer, std::true_type) {
            for (size_t i = 0; i < _length; i++) {
                newBuffer[i] = buffer[i];
            }
        }
#endif
};
