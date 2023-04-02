// A Program that prints letters based upon user inputs
//Fadi Al hatu z5309136
//26/09/2021

#include <stdio.h>
int main (void) {
    
    char upper_or_lower;
    int alpha;
    
    printf("Uppercase: ");
    scanf("%c", &upper_or_lower);
    if (!(upper_or_lower == 'y' || upper_or_lower == 'n')) {
        printf("You need to enter 'y' or 'n'\n");
        printf("Exiting the program with error code 1\n");
    }
    else {
        printf("Index: "); 
        scanf("%d", &alpha);
        
        if (alpha<=0 || alpha >= 27) {
        printf("You need to enter a number between 1 and 26 inclusive\n");
        printf("Exiting the program with error code 2\n");
        }
        else {
            if (upper_or_lower == 'y') {
                char userletter = alpha + 64;
                printf("The letter is %c\n", userletter);
                }
            else {
            char userletter = alpha + 96;
            printf("The letter is %c\n", userletter);
            }
        }
    }
    return 0;
} 
        
        
