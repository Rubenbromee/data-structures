#include "hash_map.h"

#include <iostream>
#include <cassert>

void run_hash_map_tests() {
    rb::hash_map<int> hashmap;

    // Test insert and get
    hashmap.insert("apple", 1);
    assert(hashmap.get("apple") == 1);
    hashmap.insert("apple", 2);
    assert(hashmap.get("apple") == 2);

    // Test basic remove
    assert(hashmap.remove("nonexistent") == false);
    hashmap.insert("banana", 3);
    assert(hashmap.search("banana") == true);
    assert(hashmap.remove("banana") == true);
    assert(hashmap.search("banana") == false);

    // Test out of range for get
    try {
        hashmap.get("banana");
        assert(false); // Should not reach here
    } catch (const std::out_of_range&) {
        assert(true); // Expected exception
    }

    // Test insert with many values
    for (int i = 0; i < 100; ++i) {
        hashmap.insert("key" + std::to_string(i), i);
    }

    // Test search and get for many values
    for (int i = 0; i < 100; ++i) {
        assert(hashmap.search("key" + std::to_string(i)) == true);
        assert(hashmap.get("key" + std::to_string(i)) == i);
    }

    // Test search for nonexistent key
    assert(hashmap.search("nonexistent") == false);

    // More insert/get tests
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

    // Test insert, search, get and remove for many values
    for (int i = 100; i < 200; ++i) {
        hashmap.insert("key" + std::to_string(i), i);
    }

    for (int i = 100; i < 200; ++i) {
        assert(hashmap.search("key" + std::to_string(i)) == true);
        assert(hashmap.get("key" + std::to_string(i)) == i);
    }
    for (int i = 100; i < 200; ++i) {
        bool removed = hashmap.remove("key" + std::to_string(i));
        bool found = hashmap.search("key" + std::to_string(i));
        assert(removed == true);
        assert(found == false);
    }

    // Test operator[]
    hashmap["apple"] = 5;
    assert(hashmap["apple"] == 5);

    hashmap["newkey"] = 10;
    assert(hashmap["newkey"] == 10);

    assert(hashmap["nonexistent"] == 0); // Default value

    // Test that inserting an empty string key throws an exception
    try {
        hashmap.insert("", 10);
        assert(false); // If we reach this line, the test has failed
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Key cannot be empty string!"); // Check that the correct exception message is thrown
    } catch (...) {
        assert(false); // If we catch any other exception, the test has failed
    }

    // Copy constructor test
    std::cout << "hashmap:" << std::endl;
    hashmap.print();
    rb::hash_map<int> hashmap_copy = hashmap;
    std::cout << "hashmap_copy:" << std::endl;
    hashmap_copy.print();
    assert(hashmap_copy["key40"] == 40);
    assert(hashmap_copy["key8"] == 8);
    assert(hashmap_copy["key58"] == 58);
    assert(hashmap_copy["key21"] == 21);
    assert(hashmap_copy["key95"] == 95);
    assert(hashmap_copy["newkey"] == 10);

    std::cout << "All hash_map tests passed!" << std::endl;
}