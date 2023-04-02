
#include <stdio.h>
int main (void) {
char game_command;
    scanf(" %c", &game_command);
    if (game_command == 't') {
                char scanned_in_value4;
                int amount;
                char scanned_in_value5;
                scanf(" %c", &scanned_in_value4);
                scanf(" %d", &amount);
                scanf(" %c", &scanned_in_value5);
    
    if (scanned_in_value4 != 'a') {
    printf("Nigga r u dumb?");
    }            
    
    else if (amount > 10) {
    printf("Nigga u too rich for this\n");
    }
    
    else {
    printf("%c %c %d %c\n",game_command, scanned_in_value4, amount, scanned_in_value5);
    }
    }
    return 0;
    }
