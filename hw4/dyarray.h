/*
    Author: Umut Dağ
    Student ID: 21801674
    Section No: 2
*/

#pragma once

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T>
class DynamicArray {
    private:
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
            reserveHelper(newBuffer, std::is_copy_constructible<T>());
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
            reserveHelper(newBuffer, std::is_copy_constructible<T>());
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

        void add(const T& value) {
            expand();

            buffer[_length++] = value;
        }

        void add(T&& value) {
            expand();

            buffer[_length++] = std::move(value);
        }

        void remove(size_t index) {
            if (index >= _length) throw std::out_of_range("Index out of range");

            // remove the item
            for (size_t i = index; i < _length - 1; i++) {
                buffer[i] = buffer[i + 1];
            }

            _length--;

            if (_shrinkOnRemove) shrink_to_fit();
        }

        T& at(size_t index) {
            if (index >= _length) throw std::out_of_range("Index out of range");

            return buffer[index];
        }
        const T& at(size_t index) const {
            if (index >= _length) throw std::out_of_range("Index out of range");

            return buffer[index];
        }

        size_t length() const noexcept { return _length; }
        size_t capacity() const noexcept { return _capacity; }

        T* data() noexcept { return buffer; }
        const T* data() const noexcept { return buffer; }

    private:
#if __cplusplus == 201103L || __cplusplus == 201402L
        void reserveHelper(T *newBuffer, std::false_type) {
            for (size_t i = 0; i < _length; i++) {
                newBuffer[i] = std::move(buffer[i]);
            }
        }

        void reserveHelper(T *newBuffer, std::true_type) {
            for (size_t i = 0; i < _length; i++) {
                newBuffer[i] = buffer[i];
            }
        }
#endif
};
