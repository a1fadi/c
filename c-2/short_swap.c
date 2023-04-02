// Swap bytes of a short

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

// given uint16_t value return the value with its bytes swapped
uint16_t short_swap(uint16_t value) {
    uint16_t swapped = 0; 
    uint16_t mask = 255;

    uint16_t second_half = value & mask ;
    mask = mask << 8;
    uint16_t first_half = value & mask;
    first_half = first_half >> 8;
    swapped = swapped | first_half;
    mask = mask >> 8;
    second_half = second_half << 8; 
    swapped = swapped | second_half;
    return swapped;
}

   