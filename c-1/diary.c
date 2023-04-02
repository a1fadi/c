
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>


int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "usage %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *homePath = getenv("HOME");
    if (homePath == NULL) {
        fprintf(stderr, "HOME not fount\n");
        return EXIT_FAILURE;
    }
    //char *diaryPath = getenv(".diary");
    int pathsize = strlen(homePath) + strlen(".diary") + 2;
    char fullPath[pathsize];
    snprintf(fullPath, pathsize, "%s/.diary", homePath);

    FILE *file = fopen(fullPath, "a");
    if (file == NULL) {
        err(EXIT_FAILURE, "failed to create %s", fullPath);
    }

    for (int i = 1; i < (argc); i++) {
        if (i == (argc - 1)) {
            fprintf(file, "%s", argv[i]);
        }
        else {
            fprintf(file, "%s ", argv[i]);
        }
    }
    fputc('\n', file);

    fclose(file);

}