#include "hash_map_util.h"
#include "hash_map.h"

#include <string>

namespace rb {
    template <typename V>
    hash_map<V>::hash_map(size_t initial_capacity) {
        table = std::vector<std::pair<std::string, V>>(initial_capacity, std::make_pair("", V()));
        capacity = initial_capacity;
        size = 0;
    }

    // Gets the index in the underlying vector of the given key
    template <typename V>
    size_t hash_map<V>::find_slot(const std::string& key) {
        size_t hash = fnv1a_hash(key);
        size_t index = hash % capacity;

        while (table[index].first != "" && table[index].first != key) {
            index = (index + 1) % capacity;
        }

        return index;
    }

    template <typename V>
    void hash_map<V>::resize() {
        size_t new_capacity = capacity * 2;
        std::vector<std::pair<std::string, V>> new_table = std::vector<std::pair<std::string, V>>(new_capacity, std::make_pair("", V()));

        for (const auto& entry : table) {
            if (entry.first != "") {
                size_t hash = fnv1a_hash(entry.first);
                size_t index = hash % new_capacity;
                while (new_table[index].first != "") {
                    index = (index + 1) % new_capacity;
                }
                new_table[index] = entry;
            }
        }

        table = std::move(new_table);
        capacity = new_capacity;
    }

    template <typename V>
    void hash_map<V>::insert(const std::string& key, const V& value) {
        if (size >= capacity / 2) {
            resize();
        }

        size_t index = find_slot(key);
        if (table[index].first == "") {
            size++;
        }

        table[index] = std:make_pair(key, value);
    }

    template <typename V>
    bool hash_map<V>::remove(const std::string& key) {
        size_t index = find_slot(key);
        if (table[index].first == key) {
            table[index].first = "";
            size--;
            return true;
        }
        return false;
    }

    template <typename V>
    V hash_map<V>::search(const std::string& key, const V& value) {
        size_t index = find_slot(key);
        if (table[index].first == key && table[index].second == value) {
            return table[index].second;
        }
        return nullptr;
    }
}