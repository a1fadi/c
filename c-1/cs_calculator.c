// A program that only calculates based upon whether the first or second number is 1 or 2
// Fadi AL Hatu
// 26/09/2021

#include <stdio.h> 
#include <math.h>
int main (void) { 
    
    
    
   /* while (scanf("%d", &scannedinvalue) != EOF) { */
    printf("Enter instruction: "); 
    int first_number;
        while (scanf("%d", &first_number) != EOF) {
         /*printf("Enter instruction: ");*/
            if (first_number == 1) {
            int i = 1;
            int scannedinvalue;
            int array_two[2] = {0};
                while (i < 2 && scanf("%d", &scannedinvalue) != EOF) {
                array_two[i] = scannedinvalue;
                i++;
                }
                int sum = array_two[1]*array_two[1];
             printf("%d\n", sum);
                 }
             else if (first_number == 2) {             
             int i = 1;
             int scannedinvalue;
             int array_two[3] = {0};
                while (i < 3 && scanf("%d", &scannedinvalue) != EOF) {
                array_two[i] = scannedinvalue;
                i++;
                }    
             int sum = pow(array_two[1], array_two[2]); 
             printf("%d\n", sum);
            }
            printf("Enter instruction: ");
            }
            
        /*
        
    
    printf
    scanf("%d %d %d", &numberone, &numbertwo, &numberthree);
    printf("%d %d %d",numberone, numbertwo, numberthree);
    
    if (numberone == 1) {
        array_one[0] = numberone;
        array_one[1] = numbertwo;
        printf("%d", array_one[1]);
    }
    
    else if (numberone == 2) {
        array_two[0] = numberone;
        array_two[1] = numbertwo;
        array_two[2] = numberthree;
        printf("%d", array_two[2]); 
    
    }
    
    if(numberone == 1) {
        scanf("%d", &numbertwo);
        int sum1 = numbertwo * numbertwo;
        printf("%d\n",sum1);
}   else if (numberone == 2) {
        scanf("%d %d", &numbertwo, &numberthree);
        float sum1 = pow(numbertwo,numberthree);
        printf("%f\n",sum1);    */

return 0;
}
