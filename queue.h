#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"

namespace rb {
    template<typename T>
    struct queue {
        private:
            node<T>* _front;
            node<T>* _rear;
        public:
            queue();
            ~queue();

            void enqueue(T value);
            void dequeue();
            void pop();
            bool empty();
            T front();
    };
}

#endif
