// A code that translates ciphertext into english
// Fadi AL hatu z5309136
// 4/11/2021

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1025

int main(void) {
int i = 0;
int a = 1; 
char letters = 0;
char code[MAX_SIZE] = {0};
code[i] = getchar();

while (code[i] != EOF) {
    while (i < strlen(code)) {
        if (code[i] >= code[a]) {
            letters = code[a];
        }
        else if (code[i] == '\0' || code[a] == '\0') {
        }
        else if (code[i] < code[a]) {
        
            letters = code[i];
        }
    
        i = i + 2;
        a = a + 2;
        printf("%c", letters);
    }
 /*   if (strlen(code) % 2 != 0) {
        printf("\n");
    } */
}
printf("\n");
return 0;
}
