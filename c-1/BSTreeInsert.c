
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <sysexits.h>

#include "BSTree.h"

BSTree BSTreeInsert(BSTree t, int val) {
	// Go through the tree to find the appropriate spot to place node
	

	if (t == NULL) {
		BSTree a = malloc(sizeof(*a));
		if (a == NULL) {
			err(EX_OSERR, "couldn't allocate BST node");
		}

		a->value = val; 
		a->left = NULL; 
		a->right = NULL;
		return a;
	}

	// recursive case 
	else if (t->value > val) {
		t->left = (BSTreeInsert(t->left, val));
	}

	else if (t->value < val) { 
		t->right = (BSTreeInsert(t->right, val));
	}
	else {
		return t; 
	}
	return t;
}

