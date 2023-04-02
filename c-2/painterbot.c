// A program that allows users to enter numbers and by the end
// when the user chooses to end the program it will print out
// a line of 0's with the number'1 in place of the 0's
// Fadi AL Hatu z5309136
// 22/06/2021

#include <stdio.h>

#define MAX_VALUE 36

int main (void) {
    int scannedinvalue;
    int results[MAX_VALUE] = { 0 };
    int i = 0; 
    
        while(scanf("%d", &scannedinvalue) == 1) {
            results[scannedinvalue] = 1;
        
            i++;
            }
           

          int a = 0;
    while (a < MAX_VALUE) {
        printf("%d", results[a]);
        a++;
        }
    printf("\n");
        
    return 0;
    }
      
            
            
            
  /*  int b = 0;
    while (b < MAX_VALUE) {
    int c = 0;
    result[b] = b;
        if (result[b] == indices[c]) {
            indices[c] = result[b];
        }
        c++;
        }
        b++;
    int f = 0;    
    while (f < MAX_VALUE) {
        if (indices[f] > 0) {
        indices[f] = 1;
        }
        else if (indices[f] == 0) {
        indices[f] = 0;
        f++;
        }
        } */
   
