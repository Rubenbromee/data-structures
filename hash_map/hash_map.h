#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <utility>
#include <vector>
#include <string>

// Hash function hashes a string either way, so key has to be a string
namespace rb {
    template <typename V>
    struct hash_map {
        private:
            std::vector<std::pair<std::string, V>> table;
            size_t size;
            size_t capacity;
            double load_factor;
            size_t growth_factor;
            size_t find_empty_slot(const std::string& key) const;
            size_t find_key_slot(const std::string& key) const;
            size_t find_slot(const std::string& key) const;
            void resize();
            
        public:
            hash_map(size_t initial_capacity = 10, double default_load_factor = 0.5, size_t default_growth_factor = 2);
            void insert(const std::string& key, const V& value);
            bool remove(const std::string& key);
            bool search(const std::string& key) const;
            V& get(const std::string& key);
            const V& get(const std::string& key) const;

            V& operator[](const std::string& key);
            const V& operator[](const std::string& key) const;

            void print_table() const; // Added function to print the table state
    };
}

#endif