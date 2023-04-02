// A program that multiplies two numbers and shows the absolute value
//Fadi AL Hatu z5309136

#include <stdio.h>
int main (void) {
int number_one;
int number_two;

    scanf("%d %d", &number_one, &number_two);
    
    int sum = number_one*number_two;
    
    if (sum == 0) {
    printf("zero\n");
    }
    
    else if (sum < 0) {
    sum = sum*-1;
    printf("%d\n", sum);
    }
    
    else {
    printf("%d\n", sum);
    }
    
    return 0;
    }
