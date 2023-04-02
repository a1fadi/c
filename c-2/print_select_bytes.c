#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage %s <source file>\n", argv[0]);
        return 1;
    }
    FILE *input = fopen(argv[1], "rb");
    
    int input_array[argc]; 
    for (int a = 2; a <argc; a++) {
        input_array[a] = atoi(argv[a]);
    }

    for (int i = 2; i <argc; i++) { 
        fseek(input, input_array[i], SEEK_SET);
        printf("%d - ", fgetc(input));

        fseek(input, input_array[i], SEEK_SET);
        printf("0x%02X - ", fgetc(input));

        fseek(input, input_array[i], SEEK_SET);
        printf("'%c'\n", fgetc(input));
    }

    fclose(input);
    return 0;

        

}


