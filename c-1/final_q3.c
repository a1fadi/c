#include <stdint.h>
#define MASK 1
/**
 * Return `1` if `value` *is* "balanced"
 * Return `0` if `value` *is not* "balanced"
 *
 * a number is said to be balanced iff it has the same number of bits set
 * set in its upper 16 bits as it does in its lower 16 bits.
 *
 * 0x10500c04 in binary, is 0b00010000010100000000110000000100
 * 0x10500c04 is balanced because there are 3 bits set in the upper 16 bits
 * and 3 bits set in the lower 16 bits
 * given 0x10500c04 final_q3 should return 1.
 *
 * 0x04300090 in binary, is 0b00000100001100000000000010010000
 * 0x04300090 is not balanced because there are 3 bits set in upper 16 bits
 * and 2 bits set in the second 16 bits.
 * given 0x04300090 final_q3 should return 0.
**/

int final_q3(uint32_t value) {
    int i = 0;
    // Have a count to see how many set bits are in first and second half 
    int count1 = 0;
    int count2 = 0;
    //while loop to count bits set in the first half 
    while (i < 16) {
        if ((value & MASK) == 1) {
            count1++;
        }
        value = value >> 1;
        i++;
    }
    // while loop to count bits in the second half 
    while (i < 32) {
        if ((value & MASK) == 1) {
            count2++;
        }
        value = value >> 1;
        i++;
    }

    //if the 2 counts are equal, return 1, else return 0
    if (count1 == count2) {
        return 1;
    }
    else {
        return 0;
    }
}
