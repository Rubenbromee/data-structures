#ifndef HASH_MAP_UTIL_H
#define HASH_MAP_UTIL_H

#include <iostream>

// 64-bit offset basis, prime number to minimize hash collisions
const size_t FNV_OFFSET_BASIS = 14695981039346656037ULL;

// 64-bit prime factor to also minimize hash collisions
const size_t FNV_PRIME = 1099511628211ULL;

inline size_t fnv1a_hash(const std::string& key) {
    size_t hash = FNV_OFFSET_BASIS; // Initialize hash with basis
    for (char c : key) { // For each byte in the string
        hash ^= c; // XOR the hash with the current byte
        hash *= FNV_PRIME; // Multiply the hash by the FNV prime
    }
    return hash;
}

#endif