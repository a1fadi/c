//A program that replies to a user's inputs
//23/09/2021
//Fadi AL Hatu 

#include <stdio.h> 

int main(void) {
    int usernumber;
    scanf("%d", &usernumber);
    
    if (usernumber > 0) {
        printf("You have entered a positive number.\n");
}   else if (usernumber < 0) {
        printf("Don't be so negative!\n");
}   else {
        printf("You have entered zero.\n");
}

return 0;
}
    
    
