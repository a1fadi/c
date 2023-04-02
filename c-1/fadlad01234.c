
#include <stdio.h>

int main(void) {

int current_WAM = 2;
int subjects_completed = 2;
int subject_onec = 2;
int subject_twoc = 2;
int subject_threec =2 ;
int subjects_taken = 2;
float total_wam;

total_wam = ((1.0*current_WAM*subjects_completed)+(subject_onec+subject_twoc+subject_threec))/(subjects_completed+subjects_taken); 

printf("%f\n", total_wam);

return 0;
}
