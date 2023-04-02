#include <err.h> 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage %s <input filename> <bytes[]>\n", argv[0]);
        return EXIT_FAILURE;
    } 

    FILE *output_stream = fopen(argv[1], "w");
    if (output_stream == NULL) {
        err(EXIT_FAILURE, "failed to open %s", argv[1]);
    }

    int number_array[argc];
    int i = 2; 
    while (i < argc) {
        number_array[i] = atoi(argv[i]);
        i++;
    }
    
    i = 2;
    while (i < argc) {
        int c = number_array[i];
        fputc(c, output_stream);
        //fprintf(output_stream, "byte %4d: %3d 0x%02x\n",i, c, c);
        i++;
    }

    fclose(output_stream);
}