// A program that prints a pattern based on how many numbers the user wants
// Fadi AL Hatu 

#include <stdio.h>
int main (void) {
    int user_number;
    
    printf("What number would you like to see: ");
    scanf("%d", &user_number);
    
    while (user_number > 1) {
        int asterix_counter = 0;        
            while (asterix_counter < user_number) {            
            printf("*");
            asterix_counter++;
}
            printf("\n");

            if (user_number % 2 == 0) {
            user_number = user_number/2;
}           else if (user_number % 2 == 1) {
            user_number = 3*user_number + 1;
}}           
return 0;
}            

