#include "dl_list.h"

#include <cassert>
#include <iostream>
#include <sstream>

void test_dl_list_constructors() {
    rb::dl_list<int> list;
    list.append(1);
    list.append(2);
    list.append(3);

    assert(list.head() == 1);
    assert(list.tail() == 3);

    rb::dl_list<int> list_copy = list;

    assert(list_copy.head() == 1);
    assert(list_copy.tail() == 3);
}

void test_append() {
    rb::dl_list<int> list;
    list.append(1);
    list.append(2);
    list.append(3);

    assert(list.head() == 1);
    assert(list.tail() == 3);

    std::cout << "test_append passed!" << std::endl;
}

void test_prepend() {
    rb::dl_list<int> list;
    list.prepend(3);
    list.prepend(2);
    list.prepend(1);

    assert(list.head() == 1);
    assert(list.tail() == 3);

    std::cout << "test_prepend passed!" << std::endl;
}

void test_insert() {
    rb::dl_list<int> list;
    list.append(1);
    list.append(2);
    list.append(4);
    list.insert(2, 3);

    assert(list.head() == 1);
    assert(list.tail() == 4);

    std::cout << "test_insert passed!" << std::endl;
}

void test_delete_node() {
    rb::dl_list<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.delete_node(3);

    assert(list.head() == 1);
    assert(list.tail() == 4);

    list.delete_node(1);
    assert(list.head() == 2);
    assert(list.tail() == 4);

    list.delete_node(4);
    assert(list.head() == 2);
    assert(list.tail() == 2);

    list.delete_node(2);
    try {
        list.head();
        assert(false); // This should not be reached
    } catch (const std::runtime_error&) {
        assert(true); // Expected to reach here
    }
    try {
        list.tail();
        assert(false); // This should not be reached
    } catch (const std::runtime_error&) {
        assert(true); // Expected to reach here
    }

    std::cout << "test_delete_node passed!" << std::endl;
}

void test_print() {
    rb::dl_list<int> list;
    list.append(10);
    list.append(20);
    list.prepend(5);

    std::ostringstream oss_forward;
    std::streambuf* cout_buf = std::cout.rdbuf();
    std::cout.rdbuf(oss_forward.rdbuf());
    list.print();
    std::cout.rdbuf(cout_buf);
    assert(oss_forward.str() == "5 10 20 \n");

    std::ostringstream oss_backward;
    std::cout.rdbuf(oss_backward.rdbuf());
    list.print_r();
    std::cout.rdbuf(cout_buf);
    assert(oss_backward.str() == "20 10 5 \n");

    std::cout << "Print test passed!" << std::endl;
}

void test_head_tail() {
    rb::dl_list<int> list;
    list.append(1);
    list.append(2);
    list.append(3);

    assert(list.head() == 1);
    assert(list.tail() == 3);

    list.delete_node(3);
    assert(list.tail() == 2);

    list.prepend(0);
    assert(list.head() == 0);

    std::cout << "test_head_tail passed!" << std::endl;
}

void run_dl_list_tests() {
    test_dl_list_constructors();
    test_append();
    test_prepend();
    test_insert();
    test_delete_node();
    test_print();
    test_head_tail();
    std::cout << "All dl_list tests passed!" << std::endl;
}