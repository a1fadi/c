// A program that indictaes whether a number is perfect or not and their associated factors
// Fadi AL Hatu

#include <stdio.h>
int main (void) {
int usernumber;

    printf("Enter number: ");
    scanf("%d", &usernumber);
    
    int divisor = 1;
    int factor_sum = 0;
        printf("The factors of %d are:\n",usernumber);
        while (divisor <= usernumber) {
            if (usernumber % divisor == 0) {
                printf("%d\n", divisor);
                factor_sum = factor_sum + divisor;
}
        divisor++;
}
        printf("Sum of factors = %d\n",factor_sum);
        if(factor_sum-usernumber == usernumber) {
            printf("%d is a perfect number\n", usernumber);
}       else {
            printf("%d is not a perfect number\n", usernumber);
}
return 0;
}
                
