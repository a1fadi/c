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
    // Create temp file as per lecture/weekly tests
    char *ending = ".tmp.final_q5";
    char temporary_pathname[strlen(argv[1]) + strlen(ending)  + 1];
    strcpy(temporary_pathname, argv[1]);
    strcat(temporary_pathname, ending);

    //open temp file for writing 
    FILE *output = fopen(temporary_pathname, "w");
    if (output == NULL) {
        err(EXIT_FAILURE, "failed to open %s", argv[1]);
    }

    //Loop through read file until the end is reached
    int c;
    int i = 1;
    while ((c = fgetc(input)) != EOF) {
        //if c = 'r' then we need to change it to '/n'
        if (c == '\r') {
            //jump forward one byte and see if the /r is proceeded by a '/n'
            fseek(input, i, SEEK_SET);
            int a = fgetc(input);
            //if so we dont want the 'c' byte so we unget it
            if (a == '\n') {
                ungetc(c, input);         
            }
            else {
                c = '\n';
            }
        }
        //output it 
        fputc(c, output);
        i++;
    }
    //close files
    fclose(input);
    fclose(output);
    //set temp back to normal
    if (rename(temporary_pathname, argv[1]) != 0) {
        err(EXIT_FAILURE, "failed to rename %s", argv[1]);

    }
}