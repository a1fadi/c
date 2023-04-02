#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

void stat_file(char *pathname);

int main(int argc, char *argv[]) {
    for (int arg = 1; arg < argc; arg++) {
        stat_file(argv[arg]);
    }
    return 0;
}

void stat_file(char *pathname) {
    //printf("stat(\"%s\", &s)\n", pathname);

    struct stat s;
    if (stat(pathname, &s) != 0) {
        perror(pathname);
        exit(1);
    }

    else {
        mode_t file_mode = s.st_mode;
        printf((S_ISDIR(file_mode)) ? "d": "-");
        printf((file_mode &S_IRUSR) ? "r": "-");
        printf((file_mode &S_IWUSR) ? "w": "-");
        printf((file_mode &S_IXUSR) ? "x": "-");
        printf((file_mode &S_IRGRP) ? "r": "-");
        printf((file_mode &S_IWGRP) ? "w": "-");
        printf((file_mode &S_IXGRP) ? "x": "-");
        printf((file_mode &S_IROTH) ? "r": "-");
        printf((file_mode &S_IWOTH) ? "w": "-");
        printf((file_mode &S_IXOTH) ? "x": "-");
        printf(" %s\n", pathname);
    }
}