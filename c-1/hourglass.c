//A program that prints out an hourglass based upon inputs
// Fadi Al Hatu weekly test
//9/10/2021

#include <stdio.h>
int main (void) {
int size;

    printf("Please enter a size: ");
    scanf("%d", &size);
    
    // For when an odd number is inputted as the size
    if (size % 2 == 1) {    
    int x = 0;
    while (x <= size/2) {
        int y = 0;   
             while (y < size) {
                if (y  >= x && y < size - x) {
                printf("*");
                }
                else {
                printf("-");
                }
                y++;
        }
        printf("\n"); 
        x++;
        }
        //For when you get past the halfway point
    while (x > size/2 && x < size) {
        int y = 0;
        while (y < size) {
            if (y >= (size - x-1) && y <= x) {
            printf ("*");
            }
            else {
            printf ("-");
            }
           y++;
        }
        printf("\n"); 
        x++;
        }
        }
        // for when an even number is inputted
        else if (size % 2 == 0) {
        int x = 0;
    while (x < size/2) {
        int y = 0;   
             while (y < size) {
                if (y  >= x && y < size - x) {
                printf("*");
                }
                else {
                printf("-");
                }
                y++;
        }
        printf("\n"); 
        x++;
        }
        //For when you get past the halfway point
    while (x >= size/2 && x < size) {
        int y = 0;
        while (y < size) {
            if (y == x-1 || y == size - x) {
                printf("*");
                }
            else if (y >= (size - x - 1) && y <= x) {
            printf ("*");
            }
            else {
            printf ("-");
            }
           y++;
        }
        printf("\n"); 
        x++;
        }
        
        }
    return 0;
    }
