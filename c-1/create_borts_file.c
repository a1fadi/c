#include <err.h> 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MASK 0xFF

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage %s <input filename> <bytes[]>\n", argv[0]);
        return EXIT_FAILURE;
    } 

    FILE *output_stream = fopen(argv[1], "w");
    if (output_stream == NULL) {
        err(EXIT_FAILURE, "failed to open %s", argv[1]);
    }

    int start = atoi(argv[2]);
    int end = atoi(argv[3]);
    int size = (end - start + 1);
    int number_array[size];
    int i = start; 
    int a = 0;
    while (i <= end) {
        number_array[a] = i;
        i++;
        a++;
    }
    
    i = 0;
    while (i < size) {
        int c = number_array[i];
        int b = c >> 8;e
        b = b & MASK;
        fputc(b, output_stream);
        int d = c << 8;
        d = c & MASK;
        fputc(d, output_stream);
        i++;
    }

    fclose(output_stream);
}