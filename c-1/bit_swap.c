// swap pairs of bits of a 64-bit value, using bitwise operators

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#define SHIFTS 32

// return value with pairs of bits swapped
uint64_t bit_swap(uint64_t value) {
    uint64_t swapped = 0;
    uint64_t mask = 1;
    uint64_t mask1 = 2;
    int i = 0; 
    while (i < SHIFTS) {
        swapped = swapped | ((value & mask) << 1);
        mask = mask << 2;
        swapped = swapped | ((value & mask1) >> 1);
        mask1 = mask1 << 2;
        i++;
    }
    return swapped;
}