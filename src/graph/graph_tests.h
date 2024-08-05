#include "graph.h"

#include <iostream>
#include <cassert>

void test_graph_constructors() {
    rb::graph g;

    g.add_edge("A", "B");
    g.add_edge("A", "C");
    g.add_edge("B", "D");
    g.add_edge("C", "D");
    g.add_edge("C", "E");
    g.add_edge("E", "F");

    rb::graph g_copy = g;

    std::cout << "g:" << std::endl;
    g.print();
    std::cout << "g_copy:" << std::endl;
    g_copy.print();
}

void test_add_edge() {
    rb::graph g;
    g.add_edge("A", "B");
    g.add_edge("A", "C");
    g.add_edge("B", "D");
    g.add_edge("C", "D");
    g.add_edge("C", "E");
    g.add_edge("E", "F");

    std::cout << "test_add_edge:" << std::endl;
    g.print();
}

void test_delete_edge() {
    rb::graph g;
    g.add_edge("A", "B");
    g.add_edge("A", "C");
    g.add_edge("B", "D");
    g.add_edge("C", "D");
    g.add_edge("C", "E");
    g.add_edge("E", "F");

    g.delete_edge("C", "D");
    g.delete_edge("C", "E");

    std::cout << "test_delete_edge:" << std::endl;
    g.print();
}

void run_graph_tests() {
    test_graph_constructors();
    test_add_edge();
    test_delete_edge();
    std::cout << "All graph tests passed!" << std::endl;
}