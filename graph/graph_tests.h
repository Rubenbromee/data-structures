#include "graph.h"
#include "graph.cpp"
#include "../dl_list/dl_list.h"
#include "../dl_list/dl_list.cpp"

#include <iostream>
#include <cassert>

void test_add_edge() {
    rb::graph g;
    g.add_edge("A", "B");
    g.add_edge("A", "C");
    g.add_edge("B", "D");
    g.add_edge("C", "D");
    g.add_edge("C", "E");
    g.add_edge("E", "F");

    std::cout << "Test add_edge:" << std::endl;
    g.print();
    std::cout << std::endl;
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

    std::cout << "Test delete_edge:" << std::endl;
    g.print();
    std::cout << std::endl;
}

void run_graph_tests() {
    test_add_edge();
    test_delete_edge();
}