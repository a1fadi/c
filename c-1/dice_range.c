// A program that shows a user expected range and average outputs of different dice and dice rolls
// 26/09/2021
// Fadi AL Hatu z5309136

#include <stdio.h>
int main(void) { 
    int dice_sides;
    int number_of_dice;
    int range_min;
    int range_max;
    float average;
    printf("Enter the number of sides on your dice: ");
    scanf("%d", &dice_sides);
    
    printf("Enter the number of dice being rolled: ");
    scanf("%d", &number_of_dice);
    
    range_min = 1*number_of_dice;
    range_max = dice_sides*number_of_dice;
    average = (range_min + range_max)/2.0;
    
    if (dice_sides <= 0) {
        printf("These dice will not produce a range.\n");
}  
    else if (number_of_dice <= 0) {
        printf("These dice will not produce a range.\n");
}   else {    
        printf("Your dice range is %d to %d.\n", range_min, range_max);
        printf("The average value is %f\n", average);
}    
    return 0;
}
