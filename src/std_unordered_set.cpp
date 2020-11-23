#include <stdint.h>
#include <unordered_set>

// typedef std::unordered_set<int64_t> hash_t;
typedef std::unordered_set<std::string> str_hash_t;

#define SETUP(n) str_hash_t str_hash; // hash_t hash;

// integers
// #define INSERT_INT_INTO_HASH(key) hash.insert(hash_t::value_type(key, value))
// #define FIND_INT_EXISTING_FROM_HASH(key) if(hash.find(key) == hash.end()) { printf("error"); exit(1); }
// #define FIND_INT_MISSING_FROM_HASH(key) if(hash.find(key) != hash.end()) { printf("error"); exit(2); }

// const char*/strings
#define INSERT_STR_INTO_HASH(key) str_hash.insert(key)
#define FIND_STR_EXISTING_FROM_HASH(key) if(str_hash.find(key) == str_hash.end()) { printf("error"); exit(3); }
#define FIND_STR_MISSING_FROM_HASH(key) if(str_hash.find(key) != str_hash.end()) { printf("error"); exit(4); }

#include "template.cpp"
