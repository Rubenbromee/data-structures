#include "list.h"

namespace rb {

    template<typename T>
    list<T>::list() {
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    template<typename T>
    list<T>::list(std::size_t initial_capacity) {
        data = new T[initial_capacity]; // Create empty c-array of type T with capacity initial capacity and point data pointer to c-array
        size = 0;
        capacity = initial_capacity;
    }

    template<typename T>
    list<T>::~list() {
        delete[] data;
    }

    template<typename T>
    void list<T>::resize(std::size_t new_capacity) {
        T* new_data = new T[new_capacity]; // Point new data pointer to empty c-array with new capacity
        // Move each element from old data to new data
        for (std::size_t i = 0; i < size; i++) {
            new_data[i] = data[i];
        }
        delete[] data; // Clean up old data object
        data = new_data; // Point current data pointer to new data
        _capacity = new_capacity; // Update current capacity to new capacity
    }

    // Appends an element to the back of the list
    template<typename T>
    void list<T>::push_back(const T& value) {
        if (_size >= _capacity) {
            std::size_t new_capacity;

            // Initial capacity set to 8 to skip a few resizes, assuming that a list usually isn't under 8 elements
            if (capacity == 0) {
                new_capacity = 8;
            } else {
                // Double capacity when size reaches capacity, to reduce number of resizes needed
                new_capacity = 2 * _capacity;
            }

            resize(new_capacity);
        }

        data[_size] = value; // Place value at end of current list
        _size++; // Increment to new size
    }

    // Removes the last element of the list
    template<typename T>
    void list<T>::pop_back() {
        // Since the memory has already been allocated, there's no use to allocate memory again for a new list
        // Just reduce the visible size by one
        if (size == 0) {
            throw std::out_of_range("Array is empty");
        }
        _size--;
    }

    // Element access
    template<typename T>
    T& list<T>::operator[](std::size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Element access on constant lists
    template<typename T>
    const T& list<T>::operator[](std::size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
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

}