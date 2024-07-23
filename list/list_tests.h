#ifndef LIST_TEST_H
#define LIST_TEST_H

#include "list.h"
#include "list.cpp" // When using templates, implementation file must also be included
#include "list_util.h"
#include <iostream>
#include <cassert>

// Util function used in intializer list constructor of list
void test_next_power_of_two() {
    // Test case where n is already a power of two
    assert(next_power_of_two(1) == 1);
    assert(next_power_of_two(2) == 2);
    assert(next_power_of_two(4) == 4);
    assert(next_power_of_two(8) == 8);
    assert(next_power_of_two(16) == 16);

    // Test case where n is not a power of two
    assert(next_power_of_two(3) == 4);
    assert(next_power_of_two(5) == 8);
    assert(next_power_of_two(6) == 8);
    assert(next_power_of_two(7) == 8);
    assert(next_power_of_two(9) == 16);
    assert(next_power_of_two(15) == 16);
    assert(next_power_of_two(17) == 32);
    assert(next_power_of_two(31) == 32);
    assert(next_power_of_two(33) == 64);

    // Test edge cases
    assert(next_power_of_two(0) == 1);  // Special case: the smallest power of two greater than or equal to 0 is 1

    // Test large numbers
    assert(next_power_of_two(1023) == 1024);
    assert(next_power_of_two(1025) == 2048);
    assert(next_power_of_two(2047) == 2048);
    assert(next_power_of_two(2049) == 4096);

    std::cout << "test_next_power_of_two passed!" << std::endl;
}

void test_constructors() {
    rb::list<int> empty_list;
    rb::list<int> list_with_set_capacity = rb::list<int>(10);
    rb::list<int> list_initialized_with_initializer_list = rb::list<int>({10, 20, 30, 40, 50});

    assert(empty_list.size() == 0);
    assert(list_with_set_capacity.capacity() == 10);
    assert(list_initialized_with_initializer_list.size() == 5);
    assert(list_initialized_with_initializer_list[0] == 10);
    assert(list_initialized_with_initializer_list[1] == 20);
    assert(list_initialized_with_initializer_list[2] == 30);
    assert(list_initialized_with_initializer_list[3] == 40);
    assert(list_initialized_with_initializer_list[4] == 50);

    std::cout << "test_constructors passed!" << std::endl;
}

void test_push_back() {
    rb::list<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    assert(list.size() == 3);
    assert(list[0] == 10);
    assert(list[1] == 20);
    assert(list[2] == 30);

    std::cout << "test_push_back passed!" << std::endl;
}

void test_pop_back() {
    rb::list<int> list;
    list.push_back(10);
    list.push_back(20);
    list.pop_back();

    assert(list.size() == 1);
    assert(list[0] == 10);

    std::cout << "test_pop_back passed!" << std::endl;
}

void test_resize() {
    rb::list<int> list;
    for (int i = 0; i < 100; i++) {
        list.push_back(i);
    }

    assert(list.size() == 100);
    assert(list[99] == 99);

    std::cout << "test_resize passed!" << std::endl;
}

void test_out_of_range() {
    rb::list<int> list;
    list.push_back(10);
    bool exception_thrown = false;

    try {
        int value = list[1];
    } catch (const std::out_of_range&) {
        exception_thrown = true;
    }

    assert(exception_thrown);

    std::cout << "test_out_of_range passed!" << std::endl;
}

void test_list_concat() {
    rb::list<int> lhs = {1, 2, 3};
    rb::list<int> rhs = {4, 5, 6};

    rb::list<int> result = list_concat(lhs, rhs);

    assert(result.size() == 6);
    assert(result[0] == 1);
    assert(result[1] == 2);
    assert(result[2] == 3);
    assert(result[3] == 4);
    assert(result[4] == 5);
    assert(result[5] == 6);

    std::cout << "test_list_concat passed!" << std::endl;
}

void test_operator_plus() {
    rb::list<int> lhs = {1, 2, 3};
    rb::list<int> rhs = {4, 5, 6};

    rb::list<int> result = lhs + rhs;

    assert(result.size() == 6);
    assert(result[0] == 1);
    assert(result[1] == 2);
    assert(result[2] == 3);
    assert(result[3] == 4);
    assert(result[4] == 5);
    assert(result[5] == 6);

    std::cout << "test_operator_plus passed!" << std::endl;
}

void run_list_test() {
    test_constructors();
    test_push_back();
    test_pop_back();
    test_resize();
    test_out_of_range();
    test_next_power_of_two();
    test_list_concat();
    test_operator_plus();
    std::cout << "All list tests passed!" << std::endl;
}

#endif