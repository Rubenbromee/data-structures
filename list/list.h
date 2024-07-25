#ifndef LIST_H
#define LIST_H

#include <initializer_list>

namespace rb {
    // A dynamic array data structure, like vector in C++ and list in Python
    template<typename T> // Generates code in compile-time depending on user specified type
    struct list {
        private:
            T* _data;
            std::size_t _size;
            std::size_t _capacity;

            void resize(std::size_t new_capacity);
        public:
            list();
            explicit list(std::size_t initial_capacity);
            list(const std::initializer_list<T>& init);
            ~list();

            void push_back(const T& value);
            void pop_back();
            T& operator[](std::size_t index);
            const T& operator[](std::size_t index) const;

            std::size_t size() const;
            std::size_t capacity() const;
            bool empty() const;
            
            /* A separate template variable U is needed here since list_concat and operator+ are not member functions
            but rather free-standing friend functions that needs to be able to concat two lists of the same generic 
            type that is not limited by the template type T */

            template<typename U>
            friend list<U> list_concat(const list<U>& lhs, const list<U>& rhs);

            template<typename U>
            friend list<U> operator+(const list<U>& lhs, const list<U>& rhs);
    };
}

#endif