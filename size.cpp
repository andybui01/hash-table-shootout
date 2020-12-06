#include <math.h>
#include <stdint.h>
#include <iostream>

#define ROUND_UP(x, y) ((((x) + (y) - 1) / (y)) * (y))

uint32_t calculateSize(uint32_t elements, double fp_rate) {

    uint32_t size = -(elements * log(fp_rate)) / pow(log(2), 2);

    // https://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
    // Alternate: round to nearest power of 2 and use bit-AND with size - 1
    // to get modulus
    // size--;
    // size |= size >> 1;
    // size |= size >> 2;
    // size |= size >> 4;
    // size |= size >> 8;
    // size |= size >> 16;
    // size++;
    // return size;

    return ROUND_UP(size, 32);
}

int main() {
    
    for (int i = 250000; i <= 3000000; i += 250000)
        std::cout << (calculateSize(i, 0.01)/8)/1000 << std::endl;

    return 0;
}