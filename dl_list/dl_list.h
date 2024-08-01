#ifndef DL_LIST_H
#define DL_LIST_H

#include "../node/dl_node.h"

#include <iostream>

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
            bool empty() const;

            // Iterator to be able to do range based for loops for the doubly linked list
            class iterator {
                public:
                    iterator(dl_node<T>* ptr) : node_ptr(ptr) {}

                    T& operator*() const { return node_ptr->data; }
                    T* operator->() const { return &(node_ptr->data); }

                    iterator& operator++() { 
                        node_ptr = node_ptr->next; 
                        return *this; 
                    }
                    iterator operator++(int) { 
                        iterator temp = *this; 
                        node_ptr = node_ptr->next; 
                        return temp; 
                    }

                    iterator& operator--() { 
                        node_ptr = node_ptr->prev; 
                        return *this; 
                    }
                    iterator operator--(int) { 
                        iterator temp = *this; 
                        node_ptr = node_ptr->prev; 
                        return temp; 
                    }

                    bool operator==(const iterator& other) const { return node_ptr == other.node_ptr; }
                    bool operator!=(const iterator& other) const { return node_ptr != other.node_ptr; }

                private:
                    dl_node<T>* node_ptr;
            };

            iterator begin() const { return iterator(_head); }
            iterator end() const { return iterator(nullptr); }
    };
}

#endif