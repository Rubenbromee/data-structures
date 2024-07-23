#include "queue.h"
#include "../node/node.h"
#include "../util/custom_exception.h"
#include <iostream>
#include <stdexcept>

namespace rb {
    template<typename T>
    queue<T>::queue() {
        _front = nullptr;
        _rear = nullptr;
    }

    // Destructor for queue
    template<typename T>
    queue<T>::~queue() {
        // Continue untill queue is empty
        while (_front != nullptr) {
            node<T>* temp = _front; // Set temporary pointer to current front
            _front = _front->next; // Set new front to current second element
            delete temp; // Delete current front
        }
        _rear = nullptr; // Set rear to nullptr just to be clear the queue has been deleted
    }

    // Adds a new element to the back of the queue
    template<typename T>
    void queue<T>::enqueue(T value) {
        node<T>* new_node = new node<T>(value);

        // If queue is empty, point both front pointer and rear pointer to new node
        if (_rear == nullptr) {
            _front = new_node;
            _rear = new_node;
            return;
        }

        _rear->next = new_node; // The current last element should point back to the new node
        _rear = new_node; // The new node is the new rear element
    }

    // Removes the front element of the queue
    template<typename T>
    void queue<T>::dequeue() {
        if (_front == nullptr) {
            throw custom_exception("Attempted dequeue of empty queue!");
            return;
        }

        node<T>* temp = _front; // Temporary pointer to be able to delete front after it has been detached from the queue
        _front = _front->next; // Set the new front to the current second node in the queue
        // If front is now nullptr, that means the last element is being dequeued, therefore the queue will be empty after the dequeue
        if (_front == nullptr) {
            _rear = nullptr;
        }
        delete temp; // Delete front after detach from queue
    }

    // Removes the front element of the queue and returns the removed element
    template<typename T>
    T queue<T>::pop() {
        if (_front == nullptr) {
            throw custom_exception("Attempted pop of empty queue!");
            return T();
        }
        node<T>* temp = _front; // Temporary pointer to be able to delete front after it has been detached from the queue
        T data = temp->data; // Store the actual data contained within the queue slot in a separate variable
        _front = _front->next; // Set the new front to the current second node in the queue
        // If front is now nullptr, that means the last element is being popped, therefore the queue will be empty after the pop
        if (_front == nullptr) {
            _rear = nullptr;
        }
        delete temp;
        return data;
    }

    // Gets the front element of the queue
    template<typename T>
    T queue<T>::front() {
        if (_front == nullptr) {
            throw custom_exception("Cannot get front of empty queue!");
            return T();
        }
        return _front->data;
    }
    
    // Checks if queue is empty
    template<typename T>
    bool queue<T>::empty() {
        return _front == nullptr;
    }
}