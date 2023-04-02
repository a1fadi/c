// Extract the 3 parts of a float using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

#define SIGN_SHIFT 31 
#define SIGN_MASK 0x1
#define EXPONENT_SHIFT 23 
#define EXPONENT_MASK 0xFF
#define FRACTION_MASK  0x7FFFFF

// separate out the 3 components of a float
float_components_t float_bits(uint32_t f) {
    float_components_t c;
    c.sign = (f >> SIGN_SHIFT) & SIGN_MASK;
    c.exponent = (f >> EXPONENT_SHIFT) & EXPONENT_MASK;
    c.fraction =  f & FRACTION_MASK;
    return c;
}


// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f) {
    return f.exponent == 0xFF && f.fraction != 0;
}

// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f) {
    return f.sign == 0 && f.exponent == 0xFF && f.fraction == 0;
}

// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f) {
    return f.sign == 1 && f.exponent == 0xFF && f.fraction == 0;
}

// given the 3 components of a float
// return 1 if it is 0 or -0, 0 otherwise
int is_zero(float_components_t f) {
    return f.exponent == 0 && f.fraction == 0;
}
