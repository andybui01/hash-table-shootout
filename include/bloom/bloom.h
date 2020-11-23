#ifndef BLOOM_H
#define BLOOM_H

#define ROUND_UP(x, y) ((((x) + (y) - 1) / (y)) * (y))
#define CEILING(x, y) (((x) + (y) - 1) / (y))

#include <math.h>
#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <functional>

#define XXH_INLINE_ALL
#include <bloom/xxhash.h>

namespace bloom {

    class bloom_filter {

    private:

        // Size of bitmap
        uint32_t size;

        // Number of hash functions used
        int num_hash;

        // False-positive rate
        double fp_rate;

        // Bitmap
        uint32_t* bitmap;

        uint32_t calculateSize(uint32_t elements, double fp_rate) {

            uint32_t size = -(elements * log(fp_rate)) / pow(log(2), 2);

            // https://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
            // Alternate: round to nearest power of 2 and use bit-AND with size - 1
            // to get modulus
            size--;
            size |= size >> 1;
            size |= size >> 2;
            size |= size >> 4;
            size |= size >> 8;
            size |= size >> 16;
            size++;
            return size;

            // return ROUND_UP(size, 32);
        }

        int calculateNumHash(uint32_t elements, uint32_t size) {
            return CEILING(size * log(2), elements);
        }

        inline void bitmap_set(uint32_t bit_index) {
            bitmap[bit_index >> 5] |= (1 << (bit_index & 31));
        }

        inline uint32_t bitmap_check(uint32_t bit_index) {
            return (bitmap[bit_index >> 5] & (1 << (bit_index & 31)));
        }



    public:
        // Constructor method, use default false-positve rate of 1%
        bloom_filter(uint32_t elements): fp_rate(0.01) {
            size = calculateSize(elements, fp_rate);
            num_hash = calculateNumHash(elements, size);
            bitmap = (uint32_t *) calloc(size / 32, 4);
        }

        // Constructor method with specified false-positive rate
        bloom_filter(uint32_t elements, double fp_rate): fp_rate(fp_rate) {
            size = calculateSize(elements, fp_rate);
            num_hash = calculateNumHash(elements, size);
            bitmap = (uint32_t *) calloc(size / 32, 4);
        }

        void insert(std::string str) {

            size_t len = str.size();
            const char* cstr = str.data();

            for (int i = 0; i < num_hash; ++i) {
                uint64_t bit_index = XXH3_64bits(cstr, len) & (size - 1);
                bitmap_set(bit_index);
            }
        }

        int find(std::string str) {

            size_t len = str.size();
            const char* cstr = str.data();

            for (int i = 0; i < num_hash; ++i) {
                uint64_t bit_index = XXH3_64bits(cstr, len) & (size - 1);
                if (!(bitmap_check(bit_index)))
                    return 0;
            }
            return 1;
        }

    };
}

#endif
