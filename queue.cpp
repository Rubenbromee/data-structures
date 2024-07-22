#include "queue.h"
#include "node.h"
#include <iostream>
#include <stdexcept>

namespace rb {
    template<typename T>
    queue<T>::queue() {
        _front = nullptr;
        _rear = nullptr;
    }

    template<typename T>
    void queue<T>::enqueue(T value) {
        node<T>* new_node = node<T>(value);

        // If queue is empty, point both front pointer and rear pointer to new node
        if (rear == nullptr) {
            _front = new_node
            _rear = new_node;
            return;
        }

        rear->next = new_node; // The current last element should point back to the new node
        rear = new_node; // The new node is the new rear element
    }

    template<typename T>
    void dequeue() {
        if (front == nullptr) {
            throw std::exception("Attempted dequeue of empty queue!");
            return;
        }

        node<T>* temp = front; // Temporary pointer to be able to delete front after it has been detached from the queue
        front = front->next; // Set the new front to the current second node in the queue
        // If front is now nullptr, that means the last element is being dequeued, therefore the queue will be empty after the dequeue
        if (front == nullptr) {
            rear = nullptr;
        }

    }
}