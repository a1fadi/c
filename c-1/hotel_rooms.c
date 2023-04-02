// 
// Written 11/10/2021
// By Fadi Al Hatu
//
// Hotel Room program
//

#include <stdio.h>

#define MAX_ROOMS 50

struct hotel {
    int room_number; 
    int capacity;
    double price;
};

// Prints the room in the correct format when given the room_number, capacity
// and price of it.
// void print_room(int room_number, int capacity, double price);

int main(void) {
int room;
int people;
    

    printf("How many rooms? ");
    scanf("%d",&room);
    
    struct hotel detail[MAX_ROOMS] = {0};
    printf("Enter hotel rooms:\n");
    int i = 0;
        while(i < room) {   
        
        scanf("%d %d %lf", &detail[i].room_number, &detail[i].capacity, &detail[i].price);
        i++;
    }

    printf("How many people? ");
    scanf("%d", &people);

    printf("Rooms that fit your group:\n");
    int a = 0;
    while (a < room) {
        if (detail[a].capacity >= people) {
            printf("Room %d (%d people) @ $%.2lf\n", detail[a].room_number, detail[a].capacity, detail[a].price);
            }
            a++;
            }
    
    

    return 0;
}

// Prints the room in the correct format when given the room_number, capacity
// and price of it.
//
// Takes in:
// - `room_number` -- The hotel room's room number.
// - `capacity` -- How many people the hotel room can fit.
// - `price` -- How much the hotel room costs.
//
// Returns: nothing. 
/*
void print_room(int room_number, int capacity, double price) {
    int a = 0;
    while (a < room) {
        if (capacity > detail[i].room_number) {
            printf("Room %d (%d people) @ $%.2lf\n", room_number, capacity, price);
            }
            a++;
            }
         

    return;
} */
