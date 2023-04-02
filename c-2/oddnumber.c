// a program that stops once you input an odd number
// 11/06/2021
// Fadi Al Hatu z5309136

#include <stdio.h>
int main(void){
    int endloop = 0;
    
    while (endloop == 0) {
    int input_number;
    printf("Please type in a number: ");
    scanf("%d", &input_number);
    if (input_number % 2 == 0) {
    printf("You may not pass, try again\n");
}   
    else {
    printf("Congratulations, you may pass:\n");
    endloop = 1;
    }
    }
    return 0;
    }
