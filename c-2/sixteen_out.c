// Convert a 16-bit signed integer to a string of binary digits

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BITS 16

char *sixteen_out(int16_t value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= INT16_MIN && l <= INT16_MAX);
        int16_t value = l;

        char *bits = sixteen_out(value);
        printf("%s\n", bits);

        free(bits);
    }

    return 0;
}

// given a signed 16 bit integer
// return a null-terminated string of 16 binary digits ('1' and '0')
// storage for string is allocated using malloc
char *sixteen_out(int16_t value) {
    char *result = malloc((N_BITS + 1) * sizeof(char));
    for (int i = 0; i < N_BITS; i++) {
        int16_t mask = 1 << (N_BITS - i - 1);
        if (value & mask) {
            result[i] = '1';
        }
        else {
            result[i] = '0';
        }
    }
    result[N_BITS] = '\0';

    return result;
    


    // PUT YOUR CODE HERE

}

