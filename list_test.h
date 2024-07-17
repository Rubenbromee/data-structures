#ifndef LIST_TEST_H
#define LIST_TEST_H

#include <iostream>
#include <cassert>
#include "list.h"
#include "list.cpp" // When using templates, implementation file must also be included

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
    rb::list<int> list;
    
}

void run_list_test() {
    test_push_back();
    test_pop_back();
    test_resize();
    test_out_of_range();
    std::cout << "All list tests passed!" << std::endl;
}

#endif