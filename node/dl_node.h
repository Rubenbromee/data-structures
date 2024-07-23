#ifndef DL_NODE_H
#define DL_NODE_H

// A doubly linked node, used for doubly linked list
namespace rb {
    template <typename T>
    struct dl_node {
        T data;
        dl_node* next;
        dl_node* prev;
        dl_node(T value) {
            data = value;
            next = nullptr;
            prev = nullptr;
        }
    };
}

#endif