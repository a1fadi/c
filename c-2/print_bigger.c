// Read 10 numbers into an array
// then print the numbers which are
// larger than the final number read.

#include <stdio.h>

int main(void) {
    int i, final_number;
    int numbers[10] = { 0 };

    i = 0;
    while (i < 10) {
        scanf("%d", &numbers[i]);
        final_number = numbers[i];
        i++;
    }
    i = 0;
    while (i < 10) {
        if (numbers[i] >= final_number) {
            printf("%d\n", numbers[i]);
        }
        i++;
    }
}
