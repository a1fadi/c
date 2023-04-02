// COMP2521 Ass2 - Police academy
// Stack data structure implementation
//
// Authors:
// Fadi Al Hatu z5309136
// Written: 5/08/2022 

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Agent.h"
#include "Map.h"
#include "Stack.h"

// Stack struct
struct stack {
    int index;
	int size;
    // Array of numbers stored in stack 
	int *array;
};

// Make new stack, initialise all values
Stack StackNew(int size) {
    Stack s = malloc(sizeof(*s));
    if (s == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    s->index = -1;
    s->size = size; 
    s->array = malloc(size * sizeof(int));
    if (s->array == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    return s;
}

// Frees all resources associated with the given stack
void StackFree(Stack s) {
    free(s->array);
    free(s);
}

// Line 43 sourced from Geeks For Geeks Stack implementation website at 25th July

// Adds an item to the top of the stack
void StackPush(Stack s, int road) {
    if (StackIsFull(s) == true) {
        return; 
    }   
    s->array[++s->index] = road;
}

// Line 54 sourced from Geeks For Geeks Stack implementation website at 25th July

// Removes an item from the top of the stack and returns it
int StackPop(Stack s) {
    if (StackIsEmpty(s) == true) {
        return - 1;
    }
    return s->array[s->index--];
}

// Line 60 sourced from Geeks For Geeks Stack implementation website at 25th July

// Returns true if the stack is empty, and false otherwise
bool StackIsEmpty(Stack s) {
    if (s->index == -1) {
        return true;
    }
    return false;
}

// Line 71 sourced from Geeks For Geeks Stack implementation website at 25th July


// Returns true if the stack is full, and false otherwise
bool StackIsFull(Stack s) {
    if (s->index == s->size -1 ) {
        return true;
    }
    return false;
}