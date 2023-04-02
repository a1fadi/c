// A program that manipulates a number to do a fibonacci sequence
// Fadi Al hatu z5309136
// 23/02/2021

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 30

void suma(int add, int number);
void printer(int add, int number);


void suma(add, number) {
    if (number < add) {
        return;
    }
    
    else {
        printer(add, number);
        return suma((add + 1), (number));
    }
}

void printer(add, number) {
    if (number < add) {
        printf("\n");
        return;
    }
    
    else {
        printf("*");
        return printer((add + 1), (number));
    }
}
    

int main(void) {
    int number; 
    while (scanf("%d", &number) != EOF) {
        int add = 1;
        suma(add, number);
    }
    return 0; 
}

