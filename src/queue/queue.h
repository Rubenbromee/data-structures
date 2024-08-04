#ifndef QUEUE_H
#define QUEUE_H

#include "../node/node.h"

// TODO: Copy assignment operator

namespace rb {
    template<typename T>
    struct queue {
        private:
            node<T>* _front;
            node<T>* _rear;
        public:
            queue() {
                _front = nullptr;
                _rear = nullptr;
            }
            
            // Copy constructor
            queue(const queue& rhs) {
                _front = nullptr;
                _rear = nullptr;
                if (!rhs.empty()) {
                    node<T>* current = rhs._front;
                    while (current) {
                        enqueue(current->data);
                        current = current->next;
                    }
                }
            }

            // Destructor for queue
            ~queue() {
                // Continue untill queue is empty
                while (_front != nullptr) {
                    node<T>* temp = _front; // Set temporary pointer to current front
                    _front = _front->next; // Set new front to current second element
                    delete temp; // Delete current front
                }
                _rear = nullptr; // Set rear to nullptr just to be clear the queue has been deleted
            }

            // Adds a new element to the back of the queue
            void enqueue(T value) {
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
            void dequeue() {
                if (_front == nullptr) {
                    throw std::runtime_error("Attempted dequeue of empty queue!");
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
            T pop() {
                if (_front == nullptr) {
                    throw std::runtime_error("Attempted pop of empty queue!");
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

            // Checks if queue is empty
            bool empty() {
                return _front == nullptr;
            }

            // Gets the front element of the queue
            T front() {
                if (_front == nullptr) {
                    throw std::runtime_error("Cannot get front of empty queue!");
                    return T();
                }
                return _front->data;
            }
    };
}

#endif
