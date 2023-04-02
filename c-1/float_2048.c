// Multiply a float by 2048 using bit operations only

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
uint32_t bits_to_float(float_components_t f);


// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -inf, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//
uint32_t float_2048(uint32_t number) {

float_components_t f = float_bits(number);
    if (f.exponent == 0xFF) {
        return number;
    }

    else if (f.exponent == 0 && f.fraction == 0) {
        return number; 
    }

    else {
        f.exponent += 11;  
        if (f.exponent >= 0xFF) {
            f.fraction = 0;
            f.exponent = 0xFF;
        }
    }
    
    return bits_to_float(f);
 
}

    float_components_t float_bits(uint32_t f) {
    float_components_t c;
    c.sign = (f >> SIGN_SHIFT) & SIGN_MASK;
    c.exponent = (f >> EXPONENT_SHIFT) & EXPONENT_MASK;
    c.fraction =  f & FRACTION_MASK;
    return c;
}

uint32_t bits_to_float(float_components_t f) {
    uint32_t answer = 0;

    answer = f.sign << SIGN_SHIFT;
    f.exponent <<= EXPONENT_SHIFT;
    answer = answer | f.exponent; 
    
    answer = answer | f.fraction; 

    return answer;
}