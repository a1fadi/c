// compile .c files specified as command line arguments
//
// if my_program.c and other_program.c is speicified as an argument then the follow two command will be executed:
// /usr/local/bin/dcc my_program.c -o my_program
// /usr/local/bin/dcc other_program.c -o other_program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spawn.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DCC_PATH "/usr/local/bin/dcc"

extern char **environ;

int main(int argc, char **argv)
{
    pid_t pid;
    for (int i = 1; i < argc; i++) {
        char *charachter = strdup(argv[i]);
        if (charachter == NULL) {
            perror("need .c");
            exit(1);
        }

        char *last_char = strchr(charachter, '.');
        if (last_char == NULL || last_char[1] != 'c' || last_char[2] != '\0') {
            fprintf(stderr, "'%s' does not end in .c\n", argv[i]);
            exit(1);
        }
        *last_char = '\0';
        char *compile[] = {DCC_PATH, argv[i], "-o", charachter, NULL};
        printf("running the command: \"");
        char **p = compile;
        while (*p) {
            printf("%s", *p);
            p++;
            if (*p) {
                printf(" ");
            }
        }
        printf("\"\n");
        if (posix_spawn(&pid, DCC_PATH, NULL, NULL, compile, environ) != 0) {
            perror("posix_spawn");
            exit(1);
        }
        int exitstat;
        if (waitpid(pid, &exitstat, 0) == -1) {
            perror("waitpid");
            exit(1);
        }
        if (exitstat != 0) {
            fprintf(stderr, "compile failed\n");
            exit(1);
        }
    }
    return 0;
}
