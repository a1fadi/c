// Call the `final_q3()' function from the command-line.
// See the exam paper and `final_q3.c' file for a description of the question.

// Do not change this file.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int final_q3(uint32_t value);

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage %s <value>\n", argv[0]);
        return EXIT_FAILURE;
    }

    uint32_t value = strtol(argv[1], NULL, 0);
    printf("final_q3(0x%08X) returned %d\n", value, final_q3(value));

    return EXIT_SUCCESS;
}
