#ifndef GRAPH_H
#define GRAPH_H

#include "../hash_map/hash_map.h"
#include "../dl_list/dl_list.h"

#include <string>
#include <iostream>

// TODO: Copy constructor, copy assignment operator

namespace rb {
    // Many-to-many directed graph data structure with the nodes being strings
    struct graph {
        private:
            rb::hash_map<rb::dl_list<std::string>> adjacency_list;
            rb::dl_list<std::string> insert_order;
        public:
            // Add an edge from node a to node b
            void add_edge(const std::string a, const std::string b) {
                // If a is a new node, add it to the insert order
                // Insert order list is used for printing
                if (!adjacency_list.search(a)) {
                    insert_order.append(a);
                }
                adjacency_list[a].append(b);
            }

            // Delete the edge from node a to node b
            void delete_edge(const std::string a, const std::string b) {
                // Attempting to delete an outgoing edge of a nonexistent node should do noting
                if (!adjacency_list.search(a)) {
                    std::cout << "Node " << a << " has no outgoing edges!";
                    return;
                }

                adjacency_list[a].delete_node(b); // Deletion of a non existent edge node will also do nothing

                /* If a has no outgoing connections, it should be removed as a key in the adjacency graph, 
                it can still exist as a value with incoming connections in the edge list of other nodes */
                if (adjacency_list[a].empty()) {
                    adjacency_list.remove(a);
                    insert_order.delete_node(a);
                }
            }

            // Print the current state of the graph
            void print() {
                // Go through all nodes in the insert order to print graph nodes based on insertion order
                for (const auto& node : insert_order) {
                    const rb::dl_list<std::string>& edges = adjacency_list[node]; // Get all edges of the current node
                    
                    // Print node and outgoing edges
                    std::cout << node << " -> ";
                    for (const auto& edge : edges) {
                        std::cout << edge << " ";
                    }
                    
                    std::cout << std::endl;
                }
            }
    };
}

#endif
