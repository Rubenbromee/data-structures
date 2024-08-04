#include "queue.h"
#include "../node/node.h"
#include <iostream>
#include <cassert>
#include <stdexcept>

void test_enqueue_dequeue() {
    rb::queue<int> q;

    // Initially, the queue should be empty
    assert(q.empty() && "Queue should be empty initially");

    // Enqueue elements
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    // Queue should not be empty
    assert(!q.empty() && "Queue should not be empty after enqueuing elements");

    // Check front element
    assert(q.front() == 10 && "Front element should be 10");

    // Dequeue elements
    q.dequeue();
    assert(q.front() == 20 && "Front element should be 20 after one dequeue");

    q.dequeue();
    assert(q.front() == 30 && "Front element should be 30 after two dequeues");

    q.dequeue();
    assert(q.empty() && "Queue should be empty after dequeuing all elements");

    std::cout << "test_enqueue_dequeue passed." << std::endl;
}

void test_pop() {
    rb::queue<int> q;

    // Enqueue elements
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    // Pop elements and check values
    assert(q.pop() == 10 && "Pop should return 10");
    assert(q.pop() == 20 && "Pop should return 20");
    assert(q.pop() == 30 && "Pop should return 30");

    // Queue should be empty after popping all elements
    assert(q.empty() && "Queue should be empty after popping all elements");

    std::cout << "test_pop passed." << std::endl;
}

void test_front_exception() {
    rb::queue<int> q;
    try {
        q.front();
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Cannot get front of empty queue!" && "Exception message should match");
        std::cout << "test_front_exception passed." << std::endl;
        return;
    }
    assert(false && "Expected exception for front() on empty queue");
}

void test_dequeue_exception() {
    rb::queue<int> q;
    try {
        q.dequeue();
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Attempted dequeue of empty queue!" && "Exception message should match");
        std::cout << "test_dequeue_exception passed." << std::endl;
        return;
    }
    assert(false && "Expected exception for dequeue() on empty queue");
}

void test_pop_exception() {
    rb::queue<int> q;
    try {
        q.pop();
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Attempted pop of empty queue!" && "Exception message should match");
        std::cout << "test_pop_exception passed." << std::endl;
        return;
    }
    assert(false && "Expected exception for pop() on empty queue");
}

void run_queue_tests() {
    test_enqueue_dequeue();
    test_pop();
    test_front_exception();
    test_dequeue_exception();
    test_pop_exception();
    std::cout << "All queue tests passed!" << std::endl;
}