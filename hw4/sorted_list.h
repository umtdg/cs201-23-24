/*
    Author: Umut Dağ
    Student ID: 21801674
    Section No: 2
*/

#pragma once

#include <algorithm>
#include <cstdlib>
#include <iostream>

template <typename T>
struct list_node {
    list_node<T> *next;
    list_node<T> *prev;
    T value;
};

template <typename T>
class sorted_list {
    private:
        list_node<T> *_head;

        size_t _length;

    public:
        sorted_list() noexcept : _head(nullptr), _length(0) {}
        ~sorted_list() {
            list_node<T> *current = _head;
            while (current != nullptr) {
                auto next = current->next;

                delete current;
                current = next;
            }
        }

        sorted_list(const sorted_list& other) {
            _head = nullptr;
            _length = 0;

            list_node<T> *current = other._head;
            while (current != nullptr) {
                insert(current->value);
                current = current->next;
            }
        }
        sorted_list(sorted_list&& other) noexcept {
            _head = std::exchange(other._head, nullptr);
            _length = std::exchange(other._length, 0);
        }

        sorted_list& operator=(const sorted_list& other) {
            if (this == &other) return *this;

            return *this = sorted_list(other);
        }
        sorted_list& operator=(sorted_list&& other) noexcept {
            if (this == &other) return *this;

            _head = std::exchange(other._head, nullptr);
            _length = std::exchange(other._length, 0);

            return *this;
        }

        size_t length() const { return _length; }

        T& front() { return _head->value; }
        const T& front() const { return _head->value; }

        list_node<T>* head() { return _head; }
        list_node<T> const* head() const { return _head; }

        list_node<T>* find(const T& value) {
            list_node<T> *current = _head;
            while (current != nullptr && current->value != value) {
                current = current->next;
            }

            return current;
        }
        list_node<T> const* find(const T& value) const {
            list_node<T> *current = _head;
            while (current != nullptr && current->value != value) {
                current = current->next;
            }

            return current;
        }

        void insert(const T& value) {
            // First item
            if (_head == nullptr) {
                insert_first(value);
                return;
            }

            // Find the first node that is greater than the value.
            // If value is larger than all, then prev has the last node
            list_node<T> *current = _head;
            list_node<T> *prev = nullptr;
            while (current != nullptr && current->value <= value) {
                prev = current;
                current = current->next;
            }

            // Insert before current or at the end
            if (current == nullptr) {
                insert_after(prev, value);
            } else {
                auto new_node = insert_before(current, value);

                // Update head if necessary
                if (current == _head) {
                    _head = new_node;
                }
            }
        }

        bool remove(const T& value) {
            list_node<T> *node = find(value);
            if (node == nullptr) return false;

            // Update head if necessary
            if (node == _head) {
                _head = node->next;
            }

            // Update next node's prev
            if (node->next != nullptr) {
                node->next->prev = node->prev;
            }

            // Update prev node's next
            if (node->prev != nullptr) {
                node->prev->next = node->next;
            }

            delete node;
            _length--;

            return true;
        }

        bool empty() const { return _length == 0; }

        void
        display(const std::string& delim,
            const std::string& end,
            bool print_none_if_empty
        ) const {
            if (_length == 0 && print_none_if_empty) {
                std::cout << "None\n";
                return;
            }

            list_node<T> *current = _head;
            while (current != nullptr) {
                std::cout << current->value;
                if (current->next != nullptr) std::cout << delim;

                current = current->next;
            }

            std::cout << end;
        }
    private:
        void insert_first(const T& value) {
            _head = new list_node<T>{nullptr, nullptr, value};
            _length++;
        }

        list_node<T>* insert_before(list_node<T> *node, const T& value) {
            if (node == nullptr) return nullptr;

            list_node<T> *new_node = new list_node<T>{node, node->prev, value};

            if (node->prev != nullptr) {
                node->prev->next = new_node;
            }
            node->prev = new_node;

            _length++;
            return new_node;
        }

        void insert_after(list_node<T> *node, const T& value) {
            if (node == nullptr) return;

            list_node<T> *new_node = new list_node<T>{node->next, node, value};

            if (node->next != nullptr) {
                node->next->prev = new_node;
            }
            node->next = new_node;

            _length++;
        }
};
