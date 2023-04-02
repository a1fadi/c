// Print on-ASCII bytes from file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h> 


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage %s <input filename> \n", argv[0]);
        return EXIT_FAILURE;
    } 
    // Open file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        err(EXIT_FAILURE, "failed to open %s", argv[1]);
    }

    int a = -1;
    int d;
    //while there are still charachters in the file 
    while ((d = fgetc(input)) != EOF) {
        //search from the end and go back to the start 
        fseek(input, a, SEEK_END);
        // if we find a newline charachter
        if ((d = fgetc(input)) == '\n') {
            int b;
            fseek(input, a + 1, SEEK_END);
            //print all the charachters in front of it
            while ((b = fgetc(input)) != EOF) {
                printf("%c", b);
            }
            a--;
        }
        a--;
    }
    //close files
    fclose(input);
}