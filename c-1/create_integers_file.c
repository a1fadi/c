#include <err.h> 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage %s <input filename> <start_range> <end_range>\n", argv[0]);
        return EXIT_FAILURE;
    } 

    FILE *output_stream = fopen(argv[1], "w");
    if (output_stream == NULL) {
        err(EXIT_FAILURE, "failed to open %s", argv[1]);
    }
    int starting_integer = atoi(argv[2]);
    int ending_integer = atoi(argv[3]);

    int i = starting_integer;
    while (i <= ending_integer) {
        fprintf(output_stream, "%d\n", i);
        i++;
    }

    fclose(output_stream);
}