#include <iostream>

const size_t FNV_OFFSET_BASIS = 14695981039346656037ULL;
const size_t FNV_PRIME = 1099511628211ULL;

size_t fnv1a_hash(const std::string& key) {
    size_t hash = FNV_OFFSET_BASIS;
    for (char c : key) {
        hash ^= c;
        hash *= FNV_PRIME;
    }
    return hash;
}