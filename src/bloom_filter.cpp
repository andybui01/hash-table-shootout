#include <stdint.h>
#include <bloom/bloom.h>

// typedef bloom::bloom_filter hash_t;
typedef bloom::bloom_filter str_hash_t;

#define SETUP(n) str_hash_t str_hash(n); \
        // hash_t hash(n);

// #define INSERT_INT_INTO_HASH(key, value) hash.insert(value)
// #define FIND_INT_EXISTING_FROM_HASH(key) if(hash.find(key) == hash.end()) { printf("error"); exit(1); }
// #define FIND_INT_MISSING_FROM_HASH(key) if(hash.find(key) != hash.end()) { printf("error"); exit(2); }

#define INSERT_STR_INTO_HASH(key) str_hash.insert(key)
#define FIND_STR_EXISTING_FROM_HASH(key) if(str_hash.find(key) == 0) { printf("error"); exit(3); }
#define FIND_STR_MISSING_FROM_HASH(key) if(str_hash.find(key) != 0) { ++false_count; }

#include "template.cpp"

