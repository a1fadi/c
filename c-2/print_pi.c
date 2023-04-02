// A program that prints out the desired number of digits of pi by the user
// Fadi Al Hatu, z5309136
//06/10/2021



#include <stdio.h>

int main (void) {
    int pi[10] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int digits;
    printf("How many digits of pi would you like to print?");
    scanf("%d", &digits);
    
    int i = 0;
    while(i < digits) {
        printf("%d",pi[i]);
        i++;
        
        if (i == digits) {
            printf("\n");
     }  
        else if (i == 1) {
            printf("."); 
     }
}
return 0;
}


