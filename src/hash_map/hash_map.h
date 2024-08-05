#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "hash_map_util.h"

#include <utility>
#include <vector>
#include <string>

namespace rb {
    template <typename V>
    struct hash_map {
        private:
            // Hash function hashes a string either way, so key has to be a string
            std::vector<std::pair<std::string, V>> table;
            size_t size;
            size_t capacity;
            double load_factor;
            size_t growth_factor;

            // Finds an empty slot where an entry with a given key can be placed, returns the index of the empty slot
            size_t find_empty_slot(const std::string& key) const {
                size_t hash = fnv1a_hash(key); // Get hash value based on key
                size_t index = hash % capacity; // Take modulo of capacity to make sure index is within bounds of table capacity

                // Try new indicies as long as the found indicies are not empty
                while (table[index].first != "") {
                    index = (index + 1) % capacity; // Compute another index that hopefully doesn't collide
                }

                return index;
            }

            // Attempts to find and occupied slot that has the same key as the given key
            size_t find_key_slot(const std::string& key) const {
                size_t hash = fnv1a_hash(key); // Get hash value based on key
                size_t index = hash % capacity; // Take modulo of capacity to make sure index is within bounds of table capacity
                size_t original_index = index; // Store original index to be able to detect infinite loop

                // Try new indicies as long as the found indicies does not contain the specified key
                while (table[index].first != key) {
                    index = (index + 1) % capacity; // Compute next index
                    // Full cycle, stop to prevent infinite loop
                    if (index == original_index) { 
                        break;
                    }
                }

                return index;
            }

            // Finds either an empty slot or the entry with the same key as the given key
            // In the case of a replacement, the occupied slot will always be found before the empty slot
            size_t find_slot(const std::string& key) const {
                size_t hash = fnv1a_hash(key); // Get hash value based on key
                size_t index = hash % capacity; // Take modulo of capacity to make sure index is within bounds of table capacity

                // Until either an empty slot or an occupied slot with the same key as the given key
                while (table[index].first != "" && table[index].first != key) {
                    index = (index + 1) % capacity; // Compute another index that hopefully doesn't collide
                }

                return index;
            }

            // Resize the table when load factor has been reached
            void resize() {
                size_t new_capacity = capacity * growth_factor; // New capacity is based on the growth factor
                // Create new table with empty key value pairs
                std::vector<std::pair<std::string, V>> new_table = std::vector<std::pair<std::string, V>>(new_capacity, std::make_pair("", V()));

                // For each entry in the old table
                for (const auto& entry : table) {
                    // If the entry is not empty
                    if (entry.first != "") {
                        size_t hash = fnv1a_hash(entry.first); // Hash the key of the current non-empty entry

                        /* Insert it into the new table according to the same logic as in find_empty_slot
                        Only here we don't care about replacement since the new table is empty and we are just filling it up 
                        Perform modulo of the hash with the new capacity to fit the new elements in the new table
                        find_empty_slot logic won't be affected since find_empty_slot uses the current capacity and as long as this logic
                        follows the logic if find_empty_slot the indicies will be found in a correct way */
                        size_t index = hash % new_capacity;
                        while (new_table[index].first != "") {
                            index = (index + 1) % new_capacity; // Compute another index that hopefully doesn't collide
                        }
                        
                        // Assign the current entry from the old table to its new slot in the new table
                        new_table[index] = std::move(entry); 
                    }
                }

                table = std::move(new_table); // Assign the newly created table as the current table of the hash map
                capacity = new_capacity; // Update the current capacity to the new capacity
            }
            
        public:
            hash_map(size_t initial_capacity = 10, double default_load_factor = 0.5, size_t default_growth_factor = 2) {
                // Initialize internal table with default constructed template values
                table = std::vector<std::pair<std::string, V>>(initial_capacity, std::make_pair("", V()));
                // Capacity is the number of total key value pairs in the internal table, value set or unset
                capacity = initial_capacity;  
                size = 0; // Size is the current number of key value pairs in the internal table with its value set
                load_factor = default_load_factor; // Factor that determines how often to resize the table
                growth_factor = default_growth_factor; // Factor that decides the table growth during a resize
            }

            ~hash_map() = default;
            
            // Copy constructor is implicit since all components of the hash map are from the standard library with existing copy-assignments

            // Insert a new key value pair into the hash map
            void insert(const std::string& key, const V& value) {
                if (key == "") {
                    throw std::runtime_error("Key cannot be empty string!");
                }

                // If the load factor has been reached, perform a resize of the hash map
                if (static_cast<double>(size) / static_cast<double>(capacity) >= load_factor) {
                    resize();
                }

                size_t index = find_slot(key); // Find an index of a free slot for the new value

                // If the key value pair has no set key, this means a new element is being inserted, therefore size is increased
                if (table[index].first == "") {
                    size++;
                }

                /* Even if it is a replacement or an insertion of a new element create a new entry 
                in the table and assign it to the table at the current index */
                table[index] = std::make_pair(key, std::move(value));
            }

            // Remove the key value pair with the given key from the hash map
            bool remove(const std::string& key) {
                size_t index = find_key_slot(key); // Find the table index of the given key

                // Ensure the found index has the given key
                if (table[index].first == key) {
                    // Overwrite the key with an empty key, essentially making it an empty slot
                    // The insert operation will consider this an empty slot since the key is an empty key
                    table[index].first = "";
                    size--; // Decrease the size since an element has been removed from the table
                    return true; // Return true, indicating a successful deletion
                }
                return false; // Otherwise return false, indicating an unsuccessful deletion
            }

            // Checks if a key value pair with a given key exists in the hash map
            bool search(const std::string& key) const {
                size_t index = find_key_slot(key); // Find the table index of the given key

                // Is the key the same as the given input
                if (table[index].first == key) {
                    return true; // Exists in hash map
                }

                return false; // Does not exist in hash map
            }

            // Gets a reference to the value of the key value pair with a given key
            V& get(const std::string& key) {
                size_t index = find_key_slot(key); // Find the table index of the given key
                
                // Is the key the same as the given input
                if (table[index].first == key) {
                    return table[index].second; // Return a reference to the value of the key value pair
                }

                throw std::out_of_range("Key not found"); // Throw an out of range exception if key is not found
            }

            // Get for constant objects
            const V& get(const std::string& key) const {
                size_t index = find_key_slot(key);
                if (table[index].first == key) {
                    return table[index].second;
                }
                throw std::out_of_range("Key not found");
            }

            // Shorthand for get operator on modifiable object
            V& operator[](const std::string& key) {
                /* Since the entry does not have to already exist on an modifiable object, 
                insert a key value pair with a default constructed value from the given key, 
                enabling syntax like: hash_map[key] = value */
                if (!search(key)) {
                    insert(key, V());
                }

                return get(key); // Return a reference to the current or default constructed value
            }

            // Shorthand for get operator on constant object
            const V& operator[](const std::string& key) const {
                return get(key); // Value can only be viewed, so a constant reference of the value is returned
            }

            // Copy-assignment operator
            hash_map<V>& operator=(const hash_map<V>& rhs) {
                // If this and rhs are not the same variable
                if (this != &rhs) {
                    table = rhs.table;
                    capacity = rhs.capacity;
                    size = rhs.size;
                    load_factor = rhs.load_factor;
                    growth_factor = rhs.growth_factor;
                }
                return *this;
            }
            
            // Prints the current table state
            void print() const {
                std::cout << "Hash table state:" << std::endl;
                for (size_t i = 0; i < capacity; ++i) {
                    if (table[i].first != "") {
                        std::cout << "Index " << i << ": " << table[i].first << " => " << table[i].second << std::endl;
                    }
                }
            }
    };
}

#endif