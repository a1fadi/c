// COMP2521 22T2 Assignment 1

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Set.h"

void testSetInsert(void);
void testSetSize(void);
void testSetContains(void);
void testSetShow(void);

void testSetUnion(void);
void testSetIntersection(void);
void testSetDifference(void);
 void testSetEquals(void);
 void testSetSubset(void);
 void testSetFloor(void);
 void testSetCeiling(void);

 void testSetCursor(void);

int main(int argc, char *argv[]) {
	testSetInsert();
	testSetSize();
	testSetContains();
	testSetShow();

    testSetUnion();
    testSetIntersection();
    testSetDifference();
	testSetEquals();
	testSetSubset();
	testSetFloor();
	testSetCeiling();

	testSetCursor();
}

void testSetInsert(void) {
	// NOTE: SetInsert can't be tested on its own unless we have direct
	//       access to the internal representation of the ADT, so you
	//       may want to #include "SetStructs.h" and then access
	//       s->tree

	Set s = SetNew();
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);
	SetInsert(s, 1);
	SetInsert(s, 3);
	assert(SetSize(s) == 6);

	SetFree(s);
}

void testSetSize(void) {
	Set s = SetNew();
	assert(SetSize(s) == 0);
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);
	assert(SetSize(s) == 4);
	SetInsert(s, 7);
	SetInsert(s, 2);
	assert(SetSize(s) == 5);

	SetFree(s);
}

void testSetContains(void) {
	Set s = SetNew();
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);
	SetInsert(s, -14);
	SetInsert(s, -4);


	assert(SetContains(s, 2));
	assert(SetContains(s, 4));
	assert(SetContains(s, 5));
	assert(SetContains(s, 8));
	assert(SetContains(s, -14));
	assert(SetContains(s, -4));
	assert(!SetContains(s, 3));
	assert(!SetContains(s, 10));

	SetFree(s);
}

void testSetShow(void) {
	// SetShow can't be tested with assert, since it prints to stdout.
	// Therefore, it must be manually checked.
	Set s = SetNew();
	SetInsert(s, 19);
	SetInsert(s, 15);
	SetInsert(s, 18);
	SetInsert(s, 8);
	SetInsert(s, 5);
	SetInsert(s, 3);
	SetInsert(s, 2);

	SetShow(s);
	printf("\n");

	SetFree(s);
}

void testSetUnion(void) {
	Set a = SetNew();
	SetInsert(a, 5);
	SetInsert(a, 2);
	SetInsert(a, 8);
	SetInsert(a, 4);
	SetInsert(a, 74);
	SetInsert(a, 89);
	SetInsert(a, 21);
	SetInsert(a, -74);
	SetInsert(a, -89);
	SetInsert(a, -21);
	SetInsert(a, 0);


	Set b = SetNew();
	SetInsert(b, 3);
	SetInsert(b, 8);
	SetInsert(b, 7);
	SetInsert(b, 9);
	SetInsert(b, 86);
	

	Set c = SetUnion(a, b);
	assert(SetContains(c, 2));
	assert(SetContains(c, 3));
	assert(SetContains(c, 21));
	assert(SetContains(c, 5));
	assert(SetContains(c, 7));
	assert(SetContains(c, 8));
	assert(SetContains(c, -74));
	assert(SetContains(c, 0));

	assert(SetSize(c) == 15);

	SetFree(a);
	SetFree(b);
	SetFree(c);
}

void testSetIntersection(void) {
	Set a = SetNew();
	SetInsert(a, 5);
	SetInsert(a, 2);
	SetInsert(a, 8);
	SetInsert(a, 4);
	SetInsert(a, -8);
	SetInsert(a, -4);
	SetInsert(a, 0);
	

	Set b = SetNew();
	SetInsert(b, 3);
	SetInsert(b, 8);
	SetInsert(b, 7);
	SetInsert(b, 5);
	SetInsert(b, -8);
	SetInsert(b, -4);
	SetInsert(b, 0);


	Set c = SetIntersection(a, b);
	assert(SetContains(c, 5));
	assert(SetContains(c, 8));
	assert(!SetContains(c, 2));
	assert(!SetContains(c, 3));
	assert(!SetContains(c, 4));
	assert(SetContains(c, -8));
	assert(SetContains(c, -4));
	assert(SetContains(c, 0));	
	assert(!SetContains(c, 7));
	assert(SetSize(c) == 5);

	Set d = SetNew();
	SetInsert(d, 5);
	SetInsert(d, 2);

	Set e = SetNew();
	SetInsert(e, 3);
	SetInsert(e, 8);
	
	Set f = SetIntersection(d, e);
	assert(!SetContains(f, 5));
	assert(!SetContains(f, 3));

	assert(SetSize(f) == 0);

	SetFree(a);
	SetFree(b);
	SetFree(c);
	SetFree(d);
	SetFree(e);
	SetFree(f);
}

void testSetDifference(void) {
	Set a = SetNew();
	SetInsert(a, 5);
	SetInsert(a, 2);
	SetInsert(a, 8);
	SetInsert(a, 4);

	Set b = SetNew();
	SetInsert(b, 3);
	SetInsert(b, 8);
	SetInsert(b, 7);
	SetInsert(b, 5);

	Set c = SetDifference(a, b);
	assert(SetContains(c, 2));
	assert(SetContains(c, 4));
	assert(!SetContains(c, 3));
	assert(!SetContains(c, 5));
	assert(!SetContains(c, 7));
	assert(!SetContains(c, 8));
	assert(SetSize(c) == 2);

	Set d = SetNew();
	SetInsert(d, 5);
	SetInsert(d, 2);

	Set e = SetNew();
	SetInsert(e, 3);
	SetInsert(e, 8);
	
	Set f = SetDifference(d, e);
	assert(SetContains(f, 5));
	assert(SetContains(f, 2));

	assert(SetSize(f) == 2);

	SetFree(a);
	SetFree(b);
	SetFree(c);
	SetFree(d);
	SetFree(e);
	SetFree(f);
}

void testSetEquals(void) {
	Set a = SetNew();
	SetInsert(a, 3);
	SetInsert(a, 7);
	SetInsert(a, 6);

	Set b = SetNew();
	SetInsert(b, 3);
	SetInsert(b, 7);
	SetInsert(b, 6);


	Set c = SetNew();
	SetInsert(c, 4102);
	SetInsert(c, 2);
	SetInsert(c, 7);
	SetInsert(c, 3);

	Set d = SetNew();
	Set e = SetNew();


	assert(SetEquals(a, b));
	assert(SetEquals(d, e));
	assert(!SetEquals(a, c));

	SetFree(a);
	SetFree(b);
	SetFree(c);
	SetFree(d);
	SetFree(e);

}

void testSetSubset(void) {
	Set a = SetNew();
	SetInsert(a, 5);
	SetInsert(a, 3);
	SetInsert(a, 6);

	Set b = SetNew();
	SetInsert(b, 3);
	SetInsert(b, 9);
	SetInsert(b, 5);
	SetInsert(b, 6);

	Set c = SetNew();
	SetInsert(c, 4);
	SetInsert(c, 2);
	SetInsert(c, 3);
	SetInsert(c, 7);

	Set d = SetNew();
	SetInsert(d, 1);

	Set e = SetNew();
	SetInsert(e, 1);



	assert(SetSubset(a, b));
	assert(!SetSubset(a, c));
	assert(SetSubset(d, e));

	SetFree(a);
	SetFree(b);
	SetFree(c);
	SetFree(d);
	SetFree(e);
}

void testSetFloor(void) {
	Set s = SetNew();
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);

	SetFloor(s, 7);

	assert(SetFloor(s, 7) == 5);
	assert(SetFloor(s, 4) == 4);
	assert(SetFloor(s, 1) == UNDEFINED);
	assert(SetFloor(s, 2) == 2);
	assert(SetFloor(s, 0) == UNDEFINED);

	SetFree(s);
}

void testSetCeiling(void) {
	Set s = SetNew();
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);

	assert(SetCeiling(s, 2) == 2);
	assert(SetCeiling(s, 6) == 8);
	assert(SetCeiling(s, 3) == 4);
	assert(SetCeiling(s, 1) == 2);
	assert(SetCeiling(s, 9) == UNDEFINED);
	assert(SetCeiling(s, 0) == 2);

	SetFree(s);
}

void testSetCursor(void) {
	Set s = SetNew();
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 105);
	SetInsert(s, 32);
	SetInsert(s, 28);
	SetInsert(s, 14);
	
	SetCursor cur = SetCursorNew(s);
	SetCursorNext(cur);
	SetCursorNext(cur);
	SetCursorNext(cur);
	SetCursorNext(cur);
	SetCursorNext(cur);
	SetCursorNext(cur);
	SetCursorNext(cur);
	SetCursorNext(cur);

	


	// assert(SetCursorNext(cur) == 2);
	// assert(SetCursorNext(cur) == 4);
	// assert(SetCursorNext(cur) == 5);
	// assert(SetCursorNext(cur) == 8);
	// assert(SetCursorNext(cur) == UNDEFINED);
	
	SetFree(s);
	SetCursorFree(cur);
}

