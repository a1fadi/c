
#include <stdio.h>

#define MAX_VALUE 36

int main (void) {
    int indices[MAX_VALUE] = { 0 };
    int scanned_in_value;
    int result = scanf("%d", &scanned_in_value);
    int i = 0; 
    
        while(scanf("%d", &indices[i]) == 1) {
        i++;           
    }
    int b = 0;
        while (b < MAX_VALUE) {
            if (indices[b] > 0) {
                 indices[b] = 1;
           
     }      else {
                indices[b] = 0;           
    }
    b++;
    }
    
      int a = 0;
    while (a < MAX_VALUE) {
        printf("%d", indices[a]);
        a++;
        }
    printf("\n");
    return 0;
    }
    
