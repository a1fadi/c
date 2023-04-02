// a program that adds numbers together
// 23/09/2021
// Fadi AL Hatu

#include <stdio.h> 
int main(void) {
    int students;
    int tutors;
    
        printf("Please enter the number of students and tutors:");
        scanf("%d %d", &students, &tutors);
        int sum = students + tutors;
        printf("%d + %d = %d\n", students, tutors, sum);
        
return 0;
}
