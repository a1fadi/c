// Implementation of the Set ADT using a balanced BST
// COMP2521 22T2 Assignment 1
// Fadi Al Hatu z5309136 30/06/2021

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Set.h"
#include "SetStructs.h"


typedef struct node *Node;
////////////////////////////////////////////////////////////////////////
// Basic Operations

/**
 * Creates a new empty set
 */
Set SetNew(void) {
	// Create new Set s and set it to NULL
	Set s = malloc(sizeof(*s));
	// If malloc fails print out fail message
	if (s == NULL) {
		fprintf(stderr, "couldn't allocate Queue\n");
		exit(EXIT_FAILURE);
	}
	s->tree = NULL; 
	return s;
}


 // Function that helps extract the tree from the given set and frees all elements of the set
static void Freetreenodes(Node s) {
	// If given tree is empty then return
	if (s == NULL) {
		return;
	}
	// Traverse through all nodes in the tree and free each node onec 'bottom' of tree is reached
	Freetreenodes(s->left);
	Freetreenodes(s->right);
	free(s);
}

// Main function that frees all memory with a given set
void SetFree(Set s) {
	if (s == NULL) {
		return;
	}
	// After freeing tree, free the entire set
	Freetreenodes(s->tree);
	free(s);
}

// HELPER FUNCTIONS REGARDING INSERTING INTO SET 

// Function that creates new node to insert to set
static Node newNode(int item) {
	// Malloc some memory to accomodate the new node
	Node new_node = malloc(sizeof(*new_node));
	if (new_node == NULL) {
		fprintf(stderr, "couldn't allocate Queue\n");
		exit(EXIT_FAILURE);
	}
	// Initialise the values of the node, as it is the newest node pointing to null  
	new_node->item = item; 
	new_node->right = NULL;
	new_node->left = NULL;
	new_node->next_biggest = UNDEFINED;
	return new_node;
}

//
// Below code (rotation and height code) was used in COMP2521 Lecture 4 AVL Trees Jiao Jiao Jiang
//

// Helper function to help rotate a tree (part of) right to satisfy AVL tree conditions
static Node RightRotate(Node s) {
	// If the tree is empty, or the tree doesnt have a left child then return
	if (s == NULL || s->left == NULL) {
		return s;
	} 
	// Make a new node point to the left child of the node we are rotating so we can manipulate it 
	Node a = s->left; 
	// The rotated node now has to carry the child of the 'new'/soon to be parent node (a)
	s->left = a->right; 
	// The rotated node now has to become a child of its new parent, as we rotate right, we make it the 
	// parents right child
	a->right = s;
	return a;
}

// Helper function to help rotate a tree (part of) right to satisfy AVL tree conditions
static Node LeftRotate(Node s) {
	// If the tree is empty, or the tree doesnt have a right child then return
	if (s == NULL || s->right == NULL) {
		return s;
	}
	// Make a new node point to the right child of the node we are rotating so we can manipulate it 
	Node a = s->right; 
	// The rotated node now has to carry the child of the 'new'/soon to be parent node (a)
	s->right = a->left;
	// The rotated node now has to become a child of its new parent, as we rotate left, we make it the 
	// parents left child 
	a->left = s;
	return a;
}

// Helper function to determine height of a tree, as we need to pick the longest route from parent to leaf
static int THeight(Node s) {
	// If tree passed in is empty, return
	if (s == NULL) {
		return 0;
	} else {
		// To calculate which tree is higher, we recursively call the THeight function adding 
		// 1 to each subtrees height until one reaches NULL
		int left_height = 1 + THeight(s->left);
		int right_height = 1 + THeight(s->right);

		// We return whichever height was highest, left subtree or right
		if (left_height > right_height) { 
			return left_height;
		} else {
			return right_height;
		}
	}
}

// The below function was influenced by the pseudo code used in the lecture 4 about AVL trees Jiao Jiao Jiang

// Helper function to help insert nodes into set, by first inserting into the sets tree
static Node InsertSetTree(Node s, int item) {
	// If the tree is empty, return a new node at the bottom of the tree with the corresponding item
	if (s == NULL) {
		s = newNode(item);
	// If the value is Undefined or there is already a node with the same item as the one trying to be inserted return
	} else if (item == UNDEFINED || s->item == item) {
		return s;
	// If the new item is less than the current item, recurse to the left
	} else if (item < s->item) {
		// If statements for cursor function to try maintain the position of the cursor
		if(s->left != NULL && s->left->left == NULL && s->left->right == NULL) {
			s->next_biggest = s->item;
		}
		else if(s->left == NULL && s->right != NULL) {
			s->next_biggest = s->item;
		}
		s->left = InsertSetTree(s->left, item);
	// If the new item is more than the current item, recurse to the right 
	} else if (item > s->item) {
		if(s->right != NULL) {
			s->next_biggest = s->item;
		}
		s->right = InsertSetTree(s->right, item);
	}
	// For balancing purposes we need to find the height of each subtree
	int left_height = THeight(s->left);
	int right_height = THeight(s->right);

	// If the left subtree is bigger than the right subtree by more than 1 then we need to rotate the node right
	if (left_height - right_height > 1) {
		// If the nodes left child is smaller than the new item, creating a 'zigzag shape' then we rotate left
		if (item > s->left->item) {
			s->left = LeftRotate(s->left);
		}
		s = RightRotate(s);
	}

	// If the right subtree is bigger than the left subtree by more than 1 then we need to rotate the node left
	else if (right_height - left_height > 1) {
		// If the nodes right child is smaller than the new item, creating a 'zigzag shape' then we rotate right
		if (item > s->right->item) {
			s->right = RightRotate(s->right);
		}
		s = LeftRotate(s);
	}
	// Return the new tree
	return s;
}

/**
 * Inserts an item into the set
 */

void SetInsert(Set s, int item) {
	//Initialise set by using AVL self balancing tree
	s->tree = InsertSetTree(s->tree, item);
	return;
}



// Helper function that counts individual nodes in tree
static int STreesize(Node s) {
	// If tree is empty, then return
	if (s == NULL) {
		return 0;
	} else {
		//Traverse through the entire tree and add 1 every time theres a non-null node
		return 1 + STreesize(s->left) + STreesize(s->right);
	}
}

/**
 * Returns the number of elements in the set
 */
int SetSize(Set s) {
	// If set is empty, then return 0
	if (s == NULL) {
		return 0;
	} else {
		// If not an empty set, then count nodes in tree
		return STreesize(s->tree);
	}
	// Return negative if theres an error
	return -1;
}

// Helper function to see if a given item exists within a tree
static int TreeContains(Node s, int item) {
	// If tree is empty, return 
	if (s == NULL) {
		return 0;
	} else if (s->item == item) {
		// If we have found the item in the tree, return 1
		return 1;
	} if (item > s->item) {
		// If the item is bigger than the current node, recurse right
		return TreeContains(s->right, item);
	} else if (item < s->item) {
		// If the item is less than current node, recurse left
		return TreeContains(s->left, item);
	}
	// If nothing is found, return 0
	return 0;
}

/**
 * Returns true if the set contains the given item, and false otherwise
 */
bool SetContains(Set s, int item) {
	// Return false if helper function returns a 0, as item wasn't found in set
	if (TreeContains(s->tree, item) == 0) {
		return false; 
	}
	// Otherwise return true
	return true;
}

//Helper Functions to help print out a given set in order
static void TreeShow(Node s, int i) {
	// If tree is empty, return
	if (s == NULL) {
		return;
	} 
	// To print in order, we recurse left, then print, then recurse right
	TreeShow(s->left, i);
	// If the item doesnt equal i (the smallest value in the tree - excluded due to formatting)
	// Then print out the value of the node with formatting
	if (s->item != i) {
		printf(", %d", s->item);
	} 
	// Recurse to the right
	TreeShow(s->right, i);
	return;
}
// Helper function to print the lowest value node in the tree with formatting requirements
static int TreeShowFirstNode(Node s) {
	// If tree is empty, return 
	if (s == NULL) {
		return 0;
	} 
	// Keep pointing to the left until we are as left as we can go (hence lowest value)
	while (s->left != NULL) {
		s = s->left;
	} 
	// Print this value without any commas as this is the lowest value
	printf("%d", s->item);
	// Return this value to help with other printing functions
	return s->item;
}
/**
 * Prints the given set in the format (in order)
 * {elem1, elem2, elem3}
 */
void SetShow(Set s) {
	// Print out formatting requirements (i.e '{}')
	printf("{");
	// Find the lowest node of the tree
	int first = TreeShowFirstNode(s->tree);
	// Print the rest of the nodes
	TreeShow(s->tree, first);
	printf("}");
	return;
}

////////////////////////////////////////////////////////////////////////
// Further Operations

/**
 * Returns a new set representing the union of the two sets
 */
static Node TreeUnion(Set c, Node a, Node b) {
	// Recurse through both trees depending on whether tree a or b is null, 
	// Add each node of each tree into new tree, as long as the data is not a duplicate
	if (b == NULL && a == NULL) {
		return NULL;
	} else if (b == NULL && a != NULL) {
		// If the new set doesnt already have an equal node, then insert node into tree
		if (TreeContains(c->tree, a->item) == false) {
			c->tree = InsertSetTree(c->tree, a->item);
		}
		TreeUnion(c,a->left,b);
		TreeUnion(c,a->right,b);
	} else if (b != NULL && a == NULL) {
		if (TreeContains(c->tree, b->item) == false) {
			c->tree = InsertSetTree(c->tree, b->item);
		}
		TreeUnion(c,a,b->left);
		TreeUnion(c,a,b->right);
	} else {
		TreeUnion(c,a->left,b->left);
		TreeUnion(c,a->right,b->right);
		if (TreeContains(c->tree, a->item) == false && (a != NULL)) {
			c->tree = InsertSetTree(c->tree, a->item);
		} if (TreeContains(c->tree, b->item) == false && (b != NULL)) {
			c->tree = InsertSetTree(c->tree, b->item);
		}
	}
	return c->tree;
}


 Set SetUnion(Set s1, Set s2) {
	// Create a new set to pass onto the helper function
	Set a = SetNew();
	a->tree = TreeUnion(a, s1->tree, s2->tree);
 	return a;
 }

/**
 * Returns a new set representing the intersection of the two sets
 */
static Node TreeIntersection(Set c, Set e, Node a) {
	// Recurse through first set's tree 
	// Add each node of each tree into new tree, as long as the data is isn't equal
	if (a == NULL) {
		return c->tree;
	}
	else {
		TreeIntersection(c, e, a->left);
		TreeIntersection(c, e, a->right);
		// If the new set doesnt already have an equal node, then insert node into tree
		if (TreeContains(e->tree, a->item) == true ) {
			c->tree = InsertSetTree(c->tree, a->item);
		}
	}
	return c->tree;
}

Set SetIntersection(Set s1, Set s2) {
	// Create new set to pass into helper function
	Set a = SetNew();
	a->tree = TreeIntersection(a, s1, s2->tree);
 	return a;
}

/**
 * Returns a new set representing the set difference s1 - s2
 */

static Node TreeDifference(Set c, Set e, Node a) {
	// Recurse first set's trees, 
	// Add each node of each tree into new tree, as long as the data is isn't equal
	if (a == NULL) {
		return c->tree;
	}
	else {
		TreeDifference(c, e, a->left);
		TreeDifference(c, e, a->right);
		// If the new set doesnt already have an equal node, then insert node into tree	
		if (TreeContains(e->tree, a->item) == false) {
			c->tree = InsertSetTree(c->tree, a->item);
		}
	}
	return c->tree;
}

Set SetDifference(Set s1, Set s2) {
	Set a = SetNew();
	a->tree = TreeDifference(a, s2, s1->tree);
 	return a;
}

/**
 * Returns true if the two sets are equal, and false otherwise
 */
bool SetEquals(Set s1, Set s2) {
	// If the size of the sets differ, they must not be equal
	if (SetSize(s1) != SetSize(s2)) {
		return false;
	}
	// If set one isnt a subset of set two then they cant be equal (as subsets can be equal)
	if ((SetSubset(s1, s2)) == false) {
		return false;
	}
	// If 2 sets are the same size and contain the same values, they must be equal
	return true;
}

//Helper function that helps to see if a given set is a subset of another set
static int TreeSubset(Set s1, Node a) {
	// if tree is empty, return 0
	if (a == NULL) {
		return 0;
	}
	// otherwise for each node in the tree, compare it to the 2nd set using a previous function
	// if the function returns true return 0
	if (SetContains(s1, a->item) == true) {
		return TreeSubset(s1, a->left) + TreeSubset(s1, a->right);
	}
	else {
		// If set contains returns false, return 1
		return 1;
	}
}

/**
 * Returns true if the first set is a set of the second, and false otherwise
 */
bool SetSubset(Set s1, Set s2) {
	// Pass the tree of the first set and second set into the helper function, 
	// if the helper function returns 0, then all the elements of the set have been 
	// matched and hence first set is a subset
	if (TreeSubset(s2, s1->tree) == 0) {
		return true; 
	}
	else {
		return false;
	}
}

// Helper function to help find the floor of a set by recursing through
int TreeFloor(Node s, int item, int floor) {
	if (s == NULL) {
		return floor;
	} 
	// Recurse through tree to each individual node and compare it to current floor
	floor = TreeFloor(s->right, item, floor);
	floor = TreeFloor(s->left, item, floor);
	// If item is less than/equal to target ´ítem' and bigger than current floor, then 
	// set new floor 
	if (s->item <= item) {
		if (s->item > floor) {
			floor = s->item;
		} return floor;
	} return floor;
}

/**
 * Finds the floor of a given item in a set
 */
int SetFloor(Set s, int item) {
	int floor = UNDEFINED;
	// Call helper function to access tree segment of set
	return TreeFloor(s->tree, item, floor);
}

int TreeCeiling(Node s, int item, int ceiling) {
	if (s == NULL) {
		return ceiling;
	} 
	// Recurse through each node of the tree 
	ceiling = TreeCeiling(s->right, item, ceiling);
	ceiling = TreeCeiling(s->left, item, ceiling);
	// If item is bigger than/equal to target ´ítem' and less than current ceiling, then 
	// set new ceiling 
	if (s->item >= item) {
		if (s->item < ceiling || ceiling == UNDEFINED) {
			ceiling = s->item;
		} return ceiling;
	} return ceiling;
}

/** 
 * Returns the ceiling of a given item in a set
 */
int SetCeiling(Set s, int item) {
	int ceiling = UNDEFINED;
	// Call helper function that accesses the tree of the set
	return TreeCeiling(s->tree, item, ceiling);
}

////////////////////////////////////////////////////////////////////////
// Cursor Operations

//Note Cursor doesnt work

/**
 * Creates a new cursor positioned at the smallest element of the set
 */
SetCursor SetCursorNew(Set s) {
	SetCursor c = malloc(sizeof(*c));
	// If malloc fails print out fail message
	if (c == NULL) {
		fprintf(stderr, "couldn't allocate Queue\n");
		exit(EXIT_FAILURE);
	}
	//Initialise cursor values 
	c->set = s; 
	c->current_item = UNDEFINED;
	return c;
}

/**
 * Frees all memory associated with the given cursor
 */
void SetCursorFree(SetCursor cur) {
	free(cur);
}

/**
 * Returns the element at the cursor's current position, and then moves
 * the cursor to the next greatest element. If there is no next greatest
 * element, then all subsequent calls to SetCursorNext on this cursor
 * should return UNDEFINED.
 */

int CursorFind(Node s, int a, int same_value_count) {
	// If the set is empty, return a new node at the bottom of the tree with the corresponding item
	if (s == NULL) {
		return a;
	// If there is already a node with the same item that has been seen before, continue recursing but increase same value count
	}   if (s->item == a) {
		same_value_count++;
	}
	// If the new item is less than the current item, recurse to the left unless the same value count is zero as it may have already 
	// recursed there previously
	if ((a < s->item && same_value_count == 0)) {
		if (s->left == NULL && s->item > a) {
			a = s->item;
			return a;
		}
		else {
			return CursorFind(s->left, a, same_value_count);	
		}
	} 
	// If the new item is more than the current item, or if we have already scanned the previous cursor number - recurse to the right
	else if (a > s->item || same_value_count == 1) {
		 if (a < s->item) {
			a = s->item;
			same_value_count--;
			return a;
		 }
		else { 
			return CursorFind(s->right, a, same_value_count);
		}
	} else if (a >= s->item && same_value_count == 1) {
		a = UNDEFINED;
		return a;
		}
	return a;
}

int SetCursorNext(SetCursor cur) {
	// Moves the cursor one spot right 
	int same_value_count = 0;
	// Returns current number that its on, passes in the tree, current item, and previous number of cursor
	cur->current_item = CursorFind(cur->set->tree, cur->current_item, same_value_count);

	return cur->current_item;
}

////////////////////////////////////////////////////////////////////////
