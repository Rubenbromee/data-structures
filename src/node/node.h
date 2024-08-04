#ifndef NODE_H
#define NODE_H

// A simple node class, used for other data structures
// Nodes have their member variables unprotected because they are used as components in other data structures and are not used as a data structure on their own
namespace rb {
    template <typename T>
    struct node {
        T data;
        node* next;
        node(T value) {
            data = value;
            next = nullptr;
        }
        ~node() {
            next = nullptr;
        }
    };
}

#endif