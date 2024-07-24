#include "dl_list.h"
#include "../node/dl_node.h"

#include <iostream>

namespace rb {
    template<typename T>
    dl_list<T>::dl_list() {
        _head = nullptr;
        _tail = nullptr;
    }

    template<typename T>
    dl_list<T>::~dl_list() {
        dl_node<T>* current = _head;
        while (current) {
            dl_node<T>* next_node = current->next; // Create pointer to next node to be able to traverse after current node has been deleted
            delete current;
            current = next_node;
        }
        
    }

    // Add a node to the back of the list
    template<typename T>
    void dl_list<T>::append(T value) {
        dl_node<T>* new_node = new dl_node<T>(value); // Create new node
        // If list is empty, set both head and tail to new node
        if (!_head) {
            _head = new_node;
            _tail = new_node;
        } else {
            _tail->next = new_node; // Point next of current last node to new node
            new_node->prev = _tail; // Point previous of newly attached node to the current last node
            _tail = new_node; // Set the newly appended node as the new last node of the list
        }
    }

    // Add a node to the front of the list
    template<typename T>
    void dl_list<T>::prepend(T value) {
        dl_node<T>* new_node = new dl_node<T>(value); // Create new node
        // If list is empty, set both head and tail to new node
        if (!_head) {
            _head = new_node;
            _tail = new_node;
        } else {
            new_node->next = _head; // Point the next of the new node to the current first node
            _head->prev = new_node; // Point the previous of the current head to the new node
            _head = new_node; // Set the new node as the new first node of the list
        }
    }

    // Insert a node after a node with a given value
    template<typename T>
    void dl_list<T>::insert(T value, T new_value) {
        dl_node<T>* current = _head;
        /* Until the end of the list has been reached (current is nullptr) and the given value has not been found, 
        iterate the current node pointer to the next node */
        while (current && current->data != value)
        {
            current = current->next;
        }

        // If the given value was not found in the list, return without doing anything
        if (!current) {
            return;
        }

        dl_node<T>* new_node = new dl_node<T>(new_value); // Create a new node with the new value
        new_node->next = current->next; // Point the next pointer of the new node to the node after the current node
        new_node->prev = current; // Point the previous pointer of the new node to the current node

        // If insert is being made on the last node (current is nullptr), the tail needs to be updated
        if (!current->next) {
            _tail = new_node;
        } else {
            // Update back-to-front connection to newly inserted node instead of current node
            current->next->prev = new_node;
        }

        // Update front-to-back connection to newly inserted node from current node, therefore inserting the new node after the current node
        current->next = new_node;
    }

    // Delete node with a given value
    template<typename T>
    void dl_list<T>::delete_node(const T& value) {
        dl_node<T>* current = _head;

        /* Until the end of the list has been reached (current is nullptr) and the given value has not been found, 
        iterate the current node pointer to the next node */
        while (current && current->data != value)
        {
            current = current->next;
        }

        // If the given value was not found in the list, return without doing anything
        if (!current) {
            return;
        }

        // Check if first node in the list is being removed (current->prev is nullptr)
        if (!current->prev) {
            _head = current->next; // Point the new head to the current second node in the list, since the first is being deleted
        } else {
            /* Re-point the node before the node being deleted to the node after the node being deleted, 
            detaching the front-to-back attachments of the node being deleted */
            current->prev->next = current->next; 
        }

        // Check if last node is being removed (current->next is nullptr)
        if (!current->next) {
            _tail = current->prev; // Point the new tail to the current second to last node in the list, since the last is being deleted
        } else {
            /* Re-point the node after the node being deleted to the node before the node being deleted,
            detaching the back-to-front attachments of the node being deleted */
            current->next->prev = current->prev;
        }
        
        /* Finally, when all front-to-back and back-to-front attachments of the node being deleted have been re-pointed,
        delete the node */
        delete current;
    }

    // If you want to use a custom struct or class you would need to implement the outstream operator since these printing functions just use standard cout

    // Print list front-to-back
    template<typename T>
    void dl_list<T>::print() const {
        // Iterate through the list front-to-back and print the data of each node using cout
        dl_node<T>* current = _head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Print list back-to-front
    template<typename T>
    void dl_list<T>::print_r() const {
        // Iterate through the list back-to-front and print the data of each node using cout
        dl_node<T>* current = _tail;
        while (current)
        {
            std::cout << current->data << " ";
            current = current->prev;
        }
        std::cout << std::endl;
    }

    template <typename T>
    T dl_list<T>::head() const {
        if (_head) {
            return _head->data;
        }
        throw std::runtime_error("Attempted to fetch head of empty list!");
    }

    template <typename T>
    T dl_list<T>::tail() const {
        if (_tail) {
            return _tail->data;
        }
        throw std::runtime_error("Attempted to fetch tail of empty list!");
    }
}