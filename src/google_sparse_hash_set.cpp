#include <stdint.h>
#include <sparsehash/sparse_hash_set>

// typedef google::sparse_hash_set<int64_t> hash_t;
typedef google::sparse_hash_set<std::string, std::hash<std::string>> str_hash_t;

#define SETUP(n) str_hash_t str_hash; \
        // hash_t hash;

// #define INSERT_INT_INTO_HASH(key, value) hash.insert(value)
// #define FIND_INT_EXISTING_FROM_HASH(key) if(hash.find(key) == hash.end()) { printf("error"); exit(1); }
// #define FIND_INT_MISSING_FROM_HASH(key) if(hash.find(key) != hash.end()) { printf("error"); exit(2); }

#define INSERT_STR_INTO_HASH(key) str_hash.insert(key)
#define FIND_STR_EXISTING_FROM_HASH(key) if(str_hash.find(key) == str_hash.end()) { printf("error"); exit(3); }
#define FIND_STR_MISSING_FROM_HASH(key) if(str_hash.find(key) != str_hash.end()) { printf("error"); exit(4); }

#include "template.cpp"

