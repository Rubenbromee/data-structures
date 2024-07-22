#include "list.h"
#include "list_util.h"
#include <initializer_list>
#include <algorithm>
#include <stdexcept>

namespace rb {
    template<typename T>
    list<T>::list() {
        _data = nullptr;
        _size = 0;
        _capacity = 0;
    }

    template<typename T>
    list<T>::list(std::size_t initial_capacity) {
        _data = new T[initial_capacity]; // Create empty c-array of type T with capacity initial capacity and point data pointer to c-array
        _size = 0;
        _capacity = initial_capacity;
    }

    template<typename T>
    list<T>::list(const std::initializer_list<T>& init) {
        _data = nullptr;
        _size = init.size();
        _capacity = next_power_of_two(init.size());
        if (_size > 0) {
            _data = new T[_capacity];
            std::copy(init.begin(), init.end(), _data);
        }
    }

    template<typename T>
    list<T>::~list() {
        delete[] _data;
    }

    template<typename T>
    void list<T>::resize(std::size_t new_capacity) {
        T* new_data = new T[new_capacity]; // Point new data pointer to empty c-array with new capacity
        // Move each element from old data to new data
        for (std::size_t i = 0; i < _size; i++) {
            new_data[i] = _data[i];
        }
        delete[] _data; // Clean up old data object
        _data = new_data; // Point current data pointer to new data
        _capacity = new_capacity; // Update current capacity to new capacity
    }

    // Appends an element to the back of the list
    template<typename T>
    void list<T>::push_back(const T& value) {
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
    template<typename T>
    void list<T>::pop_back() {
        // Since the memory has already been allocated, there's no use to allocate memory again for a new list
        // Just reduce the visible size by one
        if (_size == 0) {
            throw std::out_of_range("Array is empty");
        }
        _size--;
    }

    // Element access
    template<typename T>
    T& list<T>::operator[](std::size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }

    // Element access on constant lists
    template<typename T>
    const T& list<T>::operator[](std::size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }

    template<typename T>
    std::size_t list<T>::size() const {
        return _size;
    }

    template<typename T>
    std::size_t list<T>::capacity() const {
        return _capacity;
    }

    template<typename T>
    bool list<T>::empty() const {
        return _size == 0;
    }

    // Concatenate two lists, neither lhs or rhs should be modified so a new list is created and returned
    template<typename U>
    list<U> list_concat(const list<U>& lhs, const list<U>& rhs) {
        list<U> result(next_power_of_two(lhs._size + rhs._size)); // Allocate memory to fit contents of lhs and rhs
        std::copy(lhs._data, lhs._data + lhs._size, result._data); // Copy data from lhs to initial memory space in result data
        std::copy(rhs._data, rhs._data + rhs._size, result._data + lhs._size); // Copy data from rhs to remaining memory space in result data
        result._size = lhs._size + rhs._size;
        return result;
    }

    // operator+ as a shorthand for list_concat
    template<typename U>
    list<U> operator+(const list<U>& list1, const list<U>& list2) {
        return list_concat(list1, list2);
    }
}