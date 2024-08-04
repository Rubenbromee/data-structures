#include "list/list.h"
#include "list/list_tests.h"
#include "queue/queue_tests.h"
#include "dl_list/dl_list_tests.h"
#include "hash_map/hash_map_tests.h"
#include "graph/graph_tests.h"

#include <iostream>

int main() {
    run_list_test();
    run_queue_tests();
    run_dl_list_tests();
    run_hash_map_tests();
    run_graph_tests();
    return 0;
}