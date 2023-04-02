// A program that manipulates a number to do a fibonacci sequence
// Fadi Al hatu z5309136
// 23/02/2021

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 30

void square(int add, int a);
void square_depth(int add, int b);

void square(add, a) {
    if (add == a) {
        return;
    }
    else {
         int b = 0;
         square_depth(add, b); 
         printf("\n");
         return square(add, a + 1);
    }
}

void square_depth(add, b) {
    if (add > b) {
        printf("*");
        return square_depth(add, b + 1);
    }
    else { 
        return;
    }
}

int main(void) {
    int number; 
    int a = 0;
    while (scanf("%d", &number) != EOF) {
        square(number, a);
    }
    return 0; 
}

