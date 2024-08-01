#ifndef GRAPH_H
#define GRAPH_H

#include "../hash_map/hash_map.h"
#include "../hash_map/hash_map.cpp"
#include "../dl_list/dl_list.h"
#include "../dl_list/dl_list.cpp"

#include <string>

namespace rb {
    // Many-to-many directed graph data structure with the nodes being strings
    struct graph {
        private:
            rb::hash_map<rb::dl_list<std::string>> adjacency_list;
            rb::dl_list<std::string> insert_order;
        public:
            void add_edge(const std::string a, const std::string b);
            void delete_edge(const std::string a, const std::string b);
            void print();
    };
}

#endif
