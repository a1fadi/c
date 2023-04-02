//Weekly test problem
//Fadi AL Hatu 

#include <stdio.h>
int main (void) {
int integer1;
int integer2;
int integer3;

    printf("Enter Integer: ");
    scanf("%d",&integer1);
    
    printf("Enter Integer: ");
    scanf("%d",&integer2);
    
    printf("Enter Integer: ");
    scanf("%d",&integer3);
    
    if (integer1 >= integer2 && integer2 >= integer3) {
    printf("Middle: %d\n", integer2);
    }
    
    else if (integer3 >= integer2 && integer2 >= integer1) {
    printf("Middle: %d\n", integer2);
    }
    
    else if (integer2 >= integer1 && integer1 >= integer3) {
    printf("Middle: %d\n", integer1);
    }
    
     else if (integer3 >= integer1 && integer1 >= integer2) {
    printf("Middle: %d\n", integer1);
    }
    
    else if (integer2 >= integer3 && integer3 >= integer1) {
    printf("Middle: %d\n", integer3);
    }
    
    else if (integer1 >= integer3 && integer3 >= integer2) {
    printf("Middle: %d\n", integer3);
    }
    
    return 0;
    }
