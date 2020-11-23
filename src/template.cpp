#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
#include <iostream>
#include <chrono>
#include <array>

// TODO When generating random values to insert in the map there is no check
// to see if duplicate random values are generated. Could improve that (but the probability is so so
// low and the impact nearly null that it's not really worth it).

static const std::array<char, 62> ALPHANUMERIC_CHARS = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

time_t time_since_epoch(){
    auto now = std::chrono::system_clock::now();
    return std::chrono::system_clock::to_time_t( now );
}

/**
 * SMALL_STRING_SIZE should be small enough so that there is no heap allocation when a std::string is created.
 */
static const std::size_t SMALL_STRING_SIZE = 15;
static const std::size_t STRING_SIZE = 50;


static const std::int64_t SEED = time_since_epoch();
static std::mt19937_64 generator(SEED);


long get_mem_usage() {
    struct rusage *data = (struct rusage *) malloc(sizeof(struct rusage));
    getrusage(0, data);
    return data->ru_maxrss;
}

std::string get_random_alphanum_string(std::size_t size) {
    std::uniform_int_distribution<std::size_t> rd_uniform(0, ALPHANUMERIC_CHARS.size() - 1);
    
    std::string str(size, '\0');
    for(std::size_t i = 0; i < size; i++) {
        str[i] = ALPHANUMERIC_CHARS[rd_uniform(generator)];
    }
    
    return str;
}

/**
 * Generate a vector [0, nb_ints) and shuffle it
 */
std::vector<std::int64_t> get_random_shuffle_range_ints(std::size_t nb_ints) {
    std::vector<std::int64_t> random_shuffle_ints(nb_ints);
    std::iota(random_shuffle_ints.begin(), random_shuffle_ints.end(), 0);
    std::shuffle(random_shuffle_ints.begin(), random_shuffle_ints.end(), generator);
    
    return random_shuffle_ints;
}

/**
 * Generate random vector of random ints between min and max.
 */
std::vector<std::int64_t> get_random_full_ints(std::size_t nb_ints, 
                                               std::int64_t min = 0, 
                                               std::int64_t max = std::numeric_limits<std::int64_t>::max()) 
{
    std::uniform_int_distribution<std::int64_t> rd_uniform(min, max);
    
    std::vector<std::int64_t> random_ints(nb_ints);
    for(std::size_t i = 0; i < random_ints.size(); i++) {
        random_ints[i] = rd_uniform(generator);
    }
    
    return random_ints;
}


std::vector<std::string> get_random_alphanum_strings(std::size_t nb_strings, std::size_t string_size) {
    std::vector<std::string> random_strings(nb_strings);
    for(std::size_t i = 0; i < random_strings.size(); i++) {
        random_strings[i] = get_random_alphanum_string(string_size);
    }
    
    return random_strings;
}

class measurements {
public:    
    measurements(): m_memory_usage_bytes_start(get_mem_usage()),
                    m_chrono_start(std::chrono::high_resolution_clock::now())
                    
    {
    }
    
    ~measurements() {
        const auto chrono_end = std::chrono::high_resolution_clock::now();
        const std::size_t memory_usage_bytes_end = get_mem_usage();
        
        const double nb_seconds = std::chrono::duration<double>(chrono_end - m_chrono_start).count();
        // On reads or delete the used bytes could be less than initially.
        const std::size_t used_memory_bytes = (memory_usage_bytes_end > m_memory_usage_bytes_start)?
                                                    memory_usage_bytes_end - m_memory_usage_bytes_start:0;

        std::cout << nb_seconds << " " << used_memory_bytes << " ";
    }
    
private:    
    std::size_t m_memory_usage_bytes_start;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_chrono_start;
};


int main(int argc, char ** argv) {
    if(argc != 3) {
        std::cout << argv[0] << " num_keys test_type" << std::endl;
        return 1;
    }
    
    const std::int64_t num_keys = std::stoll(argv[1]);
    const std::string test_type = argv[2];

    int false_count = 0;

    SETUP(num_keys)


    /**
     * Integers
     */
    // if(test_type == "insert_random_shuffle_range") {
    //     const std::vector<std::int64_t> keys = get_random_shuffle_range_ints(num_keys);
        
        
    //     measurements m;
    //     for(std::int64_t i = 0; i < num_keys; i++) {
    //         INSERT_INT_INTO_HASH(keys[i], value);
    //     }
    // }

    // else if(test_type == "read_random_shuffle_range") {
    //     std::vector<std::int64_t> keys = get_random_shuffle_range_ints(num_keys);
    //     for(std::int64_t i = 0; i < num_keys; i++) {
    //         INSERT_INT_INTO_HASH(keys[i], value);
    //     }
        
    //     std::shuffle(keys.begin(), keys.end(), generator);
        
        
    //     measurements m;
    //     for(std::int64_t i = 0; i < num_keys; i++) {
    //         FIND_INT_EXISTING_FROM_HASH(keys[i]);
    //     }
    // }

    // else if(test_type == "insert_random_full") {
    //     const std::vector<std::int64_t> keys = get_random_full_ints(num_keys);
        
        
    //     measurements m;
    //     for(std::int64_t i = 0; i < num_keys; i++) {
    //         INSERT_INT_INTO_HASH(keys[i], value);
    //     }
    // }

    // else if(test_type == "read_random_full") {
    //     std::vector<std::int64_t> keys = get_random_full_ints(num_keys);
    //     for(std::int64_t i = 0; i < num_keys; i++) {
    //         INSERT_INT_INTO_HASH(keys[i], value);
    //     }
        
    //     std::shuffle(keys.begin(), keys.end(), generator);
        
        
    //     measurements m;
    //     for(std::int64_t i = 0; i < num_keys; i++) {
    //         FIND_INT_EXISTING_FROM_HASH(keys[i]);
    //     }
    // }

    // else if(test_type == "read_miss_random_full") {
    //     const std::vector<std::int64_t> keys_insert = get_random_full_ints(num_keys, 0, std::numeric_limits<std::int64_t>::max());
    //     const std::vector<std::int64_t> keys_read = get_random_full_ints(num_keys, std::numeric_limits<std::int64_t>::min(), -3);
        
    //     for(std::int64_t i = 0; i < num_keys; i++) {
    //         INSERT_INT_INTO_HASH(keys_insert[i], value);
    //     }
        
        
    //     measurements m;
    //     for(std::int64_t i = 0; i < num_keys; i++) {
    //         FIND_INT_MISSING_FROM_HASH(keys_read[i]);
    //     }
    // }

    /**
     * Small strings
     */
    if(test_type == "insert_small_string") {
        const std::vector<std::string> keys = get_random_alphanum_strings(num_keys, SMALL_STRING_SIZE);
        
        
        measurements m;
        for(std::int64_t i = 0; i < num_keys; i++) {
            INSERT_STR_INTO_HASH(keys[i]);
        }
    }


    else if(test_type == "read_small_string") {
        std::vector<std::string> keys = get_random_alphanum_strings(num_keys, SMALL_STRING_SIZE);
        for(std::int64_t i = 0; i < num_keys; i++) {
            INSERT_STR_INTO_HASH(keys[i]);
        }
        
        std::shuffle(keys.begin(), keys.end(), generator);
        
        
        measurements m;
        for(std::int64_t i = 0; i < num_keys; i++) {
            FIND_STR_EXISTING_FROM_HASH(keys[i]);
        }
    }

    else if(test_type == "read_miss_small_string") {
        const std::vector<std::string> keys_insert = get_random_alphanum_strings(num_keys, SMALL_STRING_SIZE);
        const std::vector<std::string> keys_read = get_random_alphanum_strings(num_keys, SMALL_STRING_SIZE);

        for(std::int64_t i = 0; i < num_keys; i++) {
            INSERT_STR_INTO_HASH(keys_insert[i]);
        }
        
        
        measurements m;
        for(std::int64_t i = 0; i < num_keys; i++) {
            FIND_STR_MISSING_FROM_HASH(keys_read[i]);
        }
    }

    /**
     * Strings
     */
    else if(test_type == "insert_string") {
        const std::vector<std::string> keys = get_random_alphanum_strings(num_keys, STRING_SIZE);
        
        
        measurements m;
        for(std::int64_t i = 0; i < num_keys; i++) {
            INSERT_STR_INTO_HASH(keys[i]);
        }
    }
    

    else if(test_type == "read_string") {
        std::vector<std::string> keys = get_random_alphanum_strings(num_keys, STRING_SIZE); 
        for(std::int64_t i = 0; i < num_keys; i++) {
            INSERT_STR_INTO_HASH(keys[i]);
        }
        
        std::shuffle(keys.begin(), keys.end(), generator);   
        
        
        measurements m;
        for(std::int64_t i = 0; i < num_keys; i++) {
            FIND_STR_EXISTING_FROM_HASH(keys[i]);
        }
    }

    else if(test_type == "read_miss_string") {
        const std::vector<std::string> keys_insert = get_random_alphanum_strings(num_keys, STRING_SIZE);
        const std::vector<std::string> keys_read = get_random_alphanum_strings(num_keys, STRING_SIZE);

        for(std::int64_t i = 0; i < num_keys; i++) {
            INSERT_STR_INTO_HASH(keys_insert[i]);
        }
        
        
        measurements m;
        for(std::int64_t i = 0; i < num_keys; i++) {
            FIND_STR_MISSING_FROM_HASH(keys_read[i]);
        }
    }

    else {
        std::cout << "Unknown test type: " << test_type << "." << std::endl;
        std::exit(1);
    }

    std::cout << false_count << std::endl;
    
}
