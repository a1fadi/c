// A program that draws out a number of boxes based upon user inputs
// Fadi AL Hatu

#include <stdio.h>
int main (void) {
    int boxes;
    
    printf("How many boxes: ");
    scanf("%d",&boxes); 
    
    int wide = (4*boxes - 1);
    int height = (4*boxes - 1);
    
    int j = 0;
        while (i < wide) {
        int i = 0;
            if(j == 0 || j == height) {
                printf("*");
            }
            else if (i == 0 || i == wide) {
                printf("*");
            }
            else if (i == wide + 1) {
                printf("\n");
            }
            i++;
            }
            j++;
                
  return 0;
  }
    
