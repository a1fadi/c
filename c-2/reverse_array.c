//A program that prints user inputs backwards
//Fadi AL Hatu
//11/10/2021

#include<stdio.h>
#define MAX 101


int main (void) {
    int numbers[MAX] = {0}; 
    printf("Enter numbers forwards:\n");
    
    int i = 0;
    while (scanf("%d", &numbers[i]) == 1) {
        i++;
    }
    
    printf("Reversed:\n");
    while (i > 0) { 
        printf("%d\n", numbers[i-1]);
        i--;
        }
    return 0;
    }
