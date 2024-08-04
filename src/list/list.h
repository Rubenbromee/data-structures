#ifndef LIST_H
#define LIST_H

#include "list_util.h"

#include <initializer_list>
#include <algorithm>
#include <stdexcept>

namespace rb {
    // A dynamic array data structure, like vector in C++ and list in Python
    template<typename T> // Generates code in compile-time depending on user specified type
    struct list {
        private:
            T* _data;
            std::size_t _size;
            std::size_t _capacity;

            void resize(std::size_t new_capacity) {
                T* new_data = new T[new_capacity]; // Point new data pointer to empty c-array with new capacity
                // Move each element from old data to new data
                for (std::size_t i = 0; i < _size; i++) {
                    new_data[i] = _data[i];
                }
                delete[] _data; // Clean up old data object
                _data = new_data; // Point current data pointer to new data
                _capacity = new_capacity; // Update current capacity to new capacity
            }

        public:
            list() {
                _data = nullptr;
                _size = 0;
                _capacity = 0;
            }

            explicit list(std::size_t initial_capacity) {
                _data = new T[initial_capacity]; // Create empty c-array of type T with capacity initial capacity and point data pointer to c-array
                _size = 0;
                _capacity = initial_capacity;
            }
            
            // Initializer list constructor, facilitating syntax like: rb::list<int>({10, 20, 30, 40, 50})
            list(const std::initializer_list<T>& init) {
                _data = nullptr;
                _size = init.size();
                _capacity = next_power_of_two(init.size());
                if (_size > 0) {
                    _data = new T[_capacity];
                    std::copy(init.begin(), init.end(), _data);
                }
            }

            // Copy constructor
            list(const list& rhs) {
                _size = rhs._size;
                _capacity = rhs._capacity;
                _data = new T[_capacity];
                std::copy(rhs._data, rhs._data + _size, _data);
            }

            ~list() {
                delete[] _data;
                _data = nullptr;
                _size = 0;
                _capacity = 0;
            }

            // Appends an element to the back of the list
            void push_back(const T& value) {
                if (_size >= _capacity) {
                    std::size_t new_capacity;

                    // Initial capacity set to 1
                    if (_capacity == 0) {
                        new_capacity = 1;
                    } else {
                        // Double capacity when size reaches capacity, to reduce number of resizes needed
                        new_capacity = 2 * _capacity;
                    }

                    resize(new_capacity);
                }

                _data[_size] = value; // Place value at end of current list
                _size++; // Increment to new size
            }

            // Removes the last element of the list
            void pop_back() {
                // Since the memory has already been allocated, there's no use to allocate memory again for a new list
                // Just reduce the visible size by one
                if (_size == 0) {
                    throw std::out_of_range("Array is empty");
                }
                _size--;
            }

            // Element access
            T& operator[](std::size_t index) {
                if (index >= _size) {
                    throw std::out_of_range("Index out of range");
                }
                return _data[index];
            }

            // Element access on constant lists
            const T& operator[](std::size_t index) const {
                if (index >= _size) {
                    throw std::out_of_range("Index out of range");
                }
                return _data[index];
            }

            std::size_t size() const {
                return _size;
            }

            std::size_t capacity() const {
                return _capacity;
            }

            bool empty() const {
                return _size == 0;
            }
            
            /* A separate template variable U is needed here since list_concat and operator+ are not member functions
            but rather free-standing friend functions that needs to be able to concat two lists of the same generic 
            type that is not limited by the template type T */

            // Concatenate two lists, neither lhs or rhs should be modified so a new list is created and returned
            template<typename U>
            friend list<U> list_concat(const list<U>& lhs, const list<U>& rhs) {
                list<U> result(next_power_of_two(lhs._size + rhs._size)); // Allocate memory to fit contents of lhs and rhs
                std::copy(lhs._data, lhs._data + lhs._size, result._data); // Copy data from lhs to initial memory space in result data
                std::copy(rhs._data, rhs._data + rhs._size, result._data + lhs._size); // Copy data from rhs to remaining memory space in result data
                result._size = lhs._size + rhs._size;
                return result;
            }
            
            // operator+ as a shorthand for list_concat
            template<typename U>
            friend list<U> operator+(const list<U>& lhs, const list<U>& rhs) {
                return list_concat(lhs, rhs);
            }

            // Copy assignment operator
            list<T>& operator=(const list& rhs) {
                if (this != &rhs) {
                    delete[] _data;  // Clean up existing resources
                    _size = rhs._size;
                    _capacity = rhs._capacity;
                    _data = new T[_capacity];
                    std::copy(rhs._data, rhs._data + _size, _data);
                }
                return *this;
            }
    };
}

#endif