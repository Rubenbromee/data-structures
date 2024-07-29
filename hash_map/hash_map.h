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
            size_t find_slot(const std::string& std::stringey);
            void resize();
        public:
            hash_map(size_t initial_capacity = 101);
            void insert(const std::string& key, const V& value);
            bool remove(const std::string& key);
            V search(const std::string& key, const V& value);
    };
}

