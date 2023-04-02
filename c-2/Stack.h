// Interface to the Stack ADT

// #ifndef STACK_H
// #define STACK_H

#include <stdbool.h>
#include <stdio.h>

#include "Map.h"

typedef struct stack *Stack;

// Creates a new empty stack
Stack StackNew(int size);

// Frees all resources associated with the given stack
void StackFree(Stack s);

// Adds an item to the top of the stack
void StackPush(Stack s, int road);

// Removes an item from the top of the stack and returns it
// Assumes that the stack is not empty
int StackPop(Stack s);

// Returns true if the stack is empty, and false otherwise
bool StackIsEmpty(Stack s);

// Returns true if the stack is full, and false otherwise
bool StackIsFull(Stack s);

