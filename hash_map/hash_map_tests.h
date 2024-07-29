#include "hash_map_util.h"
#include "hash_map.h"
#include "hash_map.cpp"

#include <iostream>
#include <cassert>

void run_hash_map_tests() {
    rb::hash_map<int> hashmap;

    hashmap.insert("apple", 1);
    assert(hashmap.get("apple") == 1);
    hashmap.insert("apple", 2);
    assert(hashmap.get("apple") == 2);

    hashmap.insert("", 10);
    assert(hashmap.search("") == true);
    assert(hashmap.get("") == 10);

    assert(hashmap.remove("nonexistent") == false);

    hashmap.insert("banana", 3);
    assert(hashmap.search("banana") == true);
    assert(hashmap.remove("banana") == true);
    assert(hashmap.search("banana") == false);

    try {
        hashmap.get("banana");
        assert(false); // Should not reach here
    } catch (const std::out_of_range&) {
        assert(true); // Expected exception
    }

    for (int i = 0; i < 100; ++i) {
        hashmap.insert("key" + std::to_string(i), i);
    }

    hashmap.print_table(); // Print the state of the table after insertions

    for (int i = 0; i < 100; ++i) {
        assert(hashmap.search("key" + std::to_string(i)) == true);
        assert(hashmap.get("key" + std::to_string(i)) == i);
    }

    assert(hashmap.search("nonexistent") == false);

    std::string key1 = "Aa";
    std::string key2 = "BB";
    hashmap.insert(key1, 100);
    hashmap.insert(key2, 200);
    assert(hashmap.get(key1) == 100);
    assert(hashmap.get(key2) == 200);

    hashmap.insert("update", 123);
    assert(hashmap.get("update") == 123);
    hashmap.insert("update", 456);
    assert(hashmap.get("update") == 456);

    for (int i = 100; i < 200; ++i) {
        hashmap.insert("key" + std::to_string(i), i);
    }

    hashmap.print_table(); // Print the state of the table after more insertions

    for (int i = 100; i < 200; ++i) {
        assert(hashmap.search("key" + std::to_string(i)) == true);
        assert(hashmap.get("key" + std::to_string(i)) == i);
    }
    for (int i = 100; i < 200; ++i) {
        bool removed = hashmap.remove("key" + std::to_string(i));
        bool found = hashmap.search("key" + std::to_string(i));
        std::cout << "Removing key" << i << ": " << (removed ? "success" : "fail") << std::endl;
        std::cout << "Searching key" << i << ": " << (found ? "found" : "not found") << std::endl;
        assert(removed == true);
        assert(found == false);
    }

    hashmap.print_table(); // Print the state of the table after removals

    // Test operator[]
    hashmap["apple"] = 5;
    assert(hashmap["apple"] == 5);

    hashmap["newkey"] = 10;
    assert(hashmap["newkey"] == 10);

    assert(hashmap["nonexistent"] == 0); // Default value

    std::cout << "All tests passed!" << std::endl;
}