// Call the `final_q7()' function from the command-line.
// See the exam paper and `final_q7.c' file for a description of the question.

// Do not change this file.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char *final_q7(char *string);

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *string = final_q7(argv[1]);
    printf("final_q7(\"%s\") returned \"%s\"\n", argv[1], string);

    assert(string != argv[1]); // Make sure the function did not modify the input string.

    free(string);

    return EXIT_SUCCESS;
}
