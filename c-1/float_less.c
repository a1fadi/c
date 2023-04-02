// Compare 2 floats using bit operations only

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

float_components_t float_bits(uint32_t f);

// float_less is given the bits of 2 floats bits1, bits2 as a uint32_t
// and returns 1 if bits1 < bits2, 0 otherwise
// 0 is return if bits1 or bits2 is Nan
// only bit operations and integer comparisons are used
uint32_t float_less(uint32_t bits1, uint32_t bits2) {
    float_components_t a = float_bits(bits1);
    float_components_t b = float_bits(bits2);

     if (is_nan(a) || is_nan(b)) {
        return 0;
    }

    if (is_zero(a) && is_zero(b)) {
        return 0;
    }

    if (is_negative_infinity(a)) {
        if (is_negative_infinity(b) == 0)
        return 1;
    }

    if (is_positive_infinity(b) && is_positive_infinity(a)) {
        return 0;
    }

    if (is_positive_infinity(b)) {
        return 1;
    }

    if (is_positive_infinity(a) || is_negative_infinity(b)) {
        return 0;
    }

    if (a.sign != b.sign) {
        if (a.sign == 1) {
            return a.sign;
        }
        else {
            return 0;
        }
    }

    if (a.exponent != b.exponent) {
        // f1, f2 have different exponents
        if (a.sign) {
            return b.exponent < a.exponent;
        } else {
            return a.exponent < b.exponent;
        }
    }

    // exponent and sign are identical
    if (a.sign) {
        return b.fraction < a.fraction;
    } else {
        return a.fraction < b.fraction;
    }

}
//Seperate the 3 components of a number
float_components_t float_bits(uint32_t f) {
    float_components_t c;
    c.sign = (f >> SIGN_SHIFT) & SIGN_MASK;
    c.exponent = (f >> EXPONENT_SHIFT) & EXPONENT_MASK;
    c.fraction =  f & FRACTION_MASK;
    return c;
}

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
