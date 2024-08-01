#include "graph.h"

#include <iostream>

namespace rb {
    // Add an edge from node a to node b
    void graph::add_edge(const std::string a, const std::string b) {
        // If a is a new node, add it to the insert order
        if (!adjacency_list.search(a)) {
            insert_order.append(a);
        }
        adjacency_list[a].append(b);
    }

    // Delete the edge from node a to node b
    void graph::delete_edge(const std::string a, const std::string b) {
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
    void graph::print() {
        // Go through all 
        for (const auto& node : insert_order) {
            // TODO: Fix copy-constructor in all data structures
            const rb::dl_list<std::string>& edges = adjacency_list[node];
            std::cout << node << " -> ";
            for (const auto& edge : edges) {
                std::cout << edge << " ";
            }
            std::cout << std::endl;
        }
    }
}