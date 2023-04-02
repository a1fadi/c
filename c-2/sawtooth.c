// A program that takes certain sizes based upon and draws sawtooth
// Fadi Al Hatu z5309136

#include <stdio.h> 
int main (void) {
int height;
int wide; 
int j;
int i;

    printf("Please enter the height of the sawtooth: ");
    scanf("%d", &height);
    printf("Please enter the length of the sawtooth: ");
    scanf("%d", &wide);
    
    j = 0;
    while (j < height) {
        i = 0;
        while (i < wide) {
            if (i % height == 0 || i % height == j) {
                printf("*");
}       else {
        printf(" ");
}       
        i++;
}
        printf("\n");
        j++;
}
return 0;
}
        
    
