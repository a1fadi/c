// A program that tells the user whether their letters are increasing or decreasing
// Fadi AL Hatu

#include <stdio.h>
int main(void) {
char charachter1;
char charachter2;
char charachter3;
    
    printf("Please enter three characters: ");
    scanf("%c %c %c", &charachter1, &charachter2, &charachter3);
    
    if (charachter1 > charachter2 && charachter2 > charachter3) {
    printf("down\n");
    }
    else if (charachter1 < charachter2 && charachter2 < charachter3) {
    printf("up\n");
    }
    else {
    printf("neither\n");
    }
    
    return 0;
}
