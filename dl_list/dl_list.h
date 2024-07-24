#ifndef DL_LIST_H
#define DL_LIST_H

#include "../node/dl_node.h"

namespace rb {
    // A doubly-linked list
    template <typename T>
    struct dl_list {
        private:
            dl_node<T>* _head;
            dl_node<T>* _tail;
        public:
            dl_list();
            ~dl_list();

            void append(T value);
            void prepend(T value);
            void insert(T value, T new_value);
            void delete_node(const T& value);
            void print() const;
            void print_r() const;
            T head() const;
            T tail() const;
    };
}

#endif