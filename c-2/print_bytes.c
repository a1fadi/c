#include <err.h> 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage %s <input filename> <start_range> <end_range>\n", argv[0]);
        return EXIT_FAILURE;
    } 

    FILE *output_stream = fopen(argv[1], "r");
    if (output_stream == NULL) {
        err(EXIT_FAILURE, "failed to open %s", argv[1]);
    }

    long i = 0;
    int c;
    while ((c = fgetc(output_stream)) != EOF) {
        printf("byte %4ld: %3d 0x%02x",i, c, c);
        if (isprint(c) != 0) { 
            printf(" '%c' ", c);
        }
        printf("\n");
        i++;
    }
    fclose(output_stream);
}