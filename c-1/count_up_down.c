//A program that counts up or down depending on the user inputs
//Fadi Al Hatu 
//z5309136

#include <stdio.h> 

int main (void) {
    int user_number;
    int counter = 0;
    printf("Enter number: ");
    scanf("%d", &user_number);
    
    if (user_number > 0) {
        while (counter <= user_number) {
            printf("%d\n",counter);
            counter++;
    }
}   
    else {
        while (counter >= user_number) {
            printf("%d\n", counter);
            counter--;  
    }
}
return 0;
}  
