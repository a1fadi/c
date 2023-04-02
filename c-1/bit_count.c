// count bits in a uint64_t

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#define NUMB_BITS 64

// return how many 1 bits value contains
int bit_count(uint64_t value) {
    int bit_counter = 0;
    int i = 0;
    uint64_t mask = 1; 
    while (i < NUMB_BITS) {
        if (mask & value) {
            bit_counter ++;
        }
        mask = mask << 1;
        i++;
    }
    return bit_counter;
}
