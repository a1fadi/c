// A program that allows users to enter numbers and by the end
// when the user chooses to end the program it will print out
// a line of 0's with the number'1 in place of the 0's
// Fadi AL Hatu z5309136
// 22/06/2021

#include <stdio.h>

#define MAX_VALUE 36

int main (void) {
    int indices[MAX_VALUE] = { 0 };
    int results[MAX_VALUE] = { 0 };
    int i = 0; 
    int scannedinvalue; 
    int result = scanf("%d", &scannedinvalue);
    
        while(i < MAX_VALUE && scanf("%d", &result) == 1) {          
            scanf("%d", &indices[i]);
            i++;
            }
                    
        int b = 0;
            while(b < MAX_VALUE) {
                int c = 0;
                while (c < MAX_VALUE) {
                    if (c == indices[b] && indices[b] > 0) {
                    results[c] = 1;
                    }
                   /* else if (indices[0] == 0) {
                    results[0] = 1;
                    } */
                    else if (c == indices[b] && indices[b] == 0) {
                    results[c] = 0;
                    }
                    
                    c++;
                    }
                    b++;                     
                    }
    int z = 0;
    while(z < MAX_VALUE) {
        if (indices[z] > 0) {
            indices[z] = 1;
            }
            z++;
            }
           
           int a = 0;
    while (a < MAX_VALUE) {
        printf("%d", results[a]);
        a++;
        }
    printf("\n");
    
    return 0;
    }
      
