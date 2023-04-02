// A program that draws an X based upon user inputs of size
// Fadi AL Hatu 2/10/2021

#include <stdio.h> 

int main (void) {
    int size;
    
    printf("Enter size: ");
    scanf("%d", &size);
    
    int row = 0;
        while (row < size) {
        int column = 0;
            while(column < size) {
                if(column == row || column == size - row-1){
                    printf("*");
}               else {
                    printf("-");
}               column++;
}    printf("\n");
     row++;     
}  
return 0;
}           
    
    
