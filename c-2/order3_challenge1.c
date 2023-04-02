// A program that orders the integer inputs of a user in ascending order withut using If or while statements, only the use of variables and printf or scanf functins
// 15/06/2021
// Fadi z5309136

#include <stdio.h>
int main(void) {
   int a;
   int b;
   int c;
   // gather input from user
   printf("Enter integer: ");
   scanf("%d", &a);
   
   printf("Enter integer: ");
   scanf("%d", &b);
   
   printf("Enter integer: ");
   scanf("%d", &c);
   
   int d;
   int e;
   int f;
   
   // Manipulate the integers
  ((a >= b && a >= c && b >= c) && (d = a, e = b, f = c));
  ((a >= b && a >= c && c >= b) && (d = a, e = c, f = b));
  ((a >= b && c >= a && c >= b) && (d = c, e = a, f = b));
  ((b >= a && a >= c && b >= c) && (d = b, e = a, f = c));
  ((b >= a && c >= a && b >= c) && (d = b, e = c, f = a));
  ((b >= a && c >= a && c >= b) && (d = c, e = b, f = a));
    
  printf("The integers in order are: %d %d %d\n", f, e, d);
  
   return 0; 
   }
   
   
