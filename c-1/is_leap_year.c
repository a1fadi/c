// a program to tell user whether a year is a leap year or not
// 26/09/2021
// Fadi Al Hatu z5309136

#include <stdio.h>

int main(void) { 
    int year;
    
    printf("Enter year: ");
    scanf("%d",&year);
    
    if (year % 4) {
        printf("%d is not a leap year.\n",year);
    }
   
   else if (year % 100) {
        printf("%d is a leap year.\n",year);
    }
    
     else if (year % 400) {
        printf("%d is not a leap year.\n",year);
    }
    
    
        
    else {
        printf("%d is a leap year.\n",year);
    }
    return 0;
    }
