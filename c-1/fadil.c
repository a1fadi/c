// A program that prints a hollow triangle based upon users inputted sizes
// 15/06/2021
// Fadi AL Hatu

#include <stdio.h> 
int main(void) {

    int height;
    int length;
    printf("Please enter the height of the sawtooth: ");
    scanf("%d", &height);
    printf("Please enter the length of the sawtooth: ");
    scanf("%d", &length);
    
    
        int sizecounter = 1;
    /* int sizecountery = 0; */
        int diagonalcounter = -1;
        while (sizecounter < height) {
        printf("*");
        if (sizecounter == 2) {
        printf ("*"); 
}
        int diagonalchaser = 0;
        while (diagonalchaser < diagonalcounter) {
            printf(" "); 
            diagonalchaser++; 
            if (diagonalcounter == diagonalchaser) {
            printf("*"); 
}
}
            printf ("\n"); 
            sizecounter ++; 
            diagonalcounter ++;}   
// When sizecounter is = to size, print the bottom row of asterixs
    if (sizecounter == height) {
    int finishcounter = 0;
    while (finishcounter < height) {
        if (finishcounter == 0 || finishcounter == height - 1)  {
        printf("*"); 
}        else {
        printf(" ");
}
    finishcounter++; }
    }
    printf("\n");
   

return 0;
}
