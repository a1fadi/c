// A program that manipulates a number to do a fibonacci sequence
// Fadi Al hatu z5309136
// 23/02/2021

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 30

int suma(add, number) {
    if (number < 1) {
        printf("*\n");
        return add;
    }
    
    else {
        printf("*\n");
        return suma((add * number), (number - 1));
    }
}
    

int main(void) {
    int number; 
    while (scanf("%d", &number) != EOF) {
        int add = 1;
        int sum1 = suma(add, number);
        printf("%d\n", sum1);
    }
    return 0; 
}

