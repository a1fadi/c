//Weekly test exercise
//Fadi AL Hat 

#include <stdio.h>
int main (void) {
int numbers;

    printf("How many numbers: ");
    scanf("%d", &numbers);
    
    int numberloop = 0;
    int sum = 0;
    while (numberloop < numbers) {
    int numbercount;
        scanf("%d", &numbercount);
        sum = sum + numbercount;
        numberloop++;
        }
    printf("The sum is: %d\n", sum);
    
    return 0;
    }
