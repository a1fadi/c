
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

BSTree BSTreeInsert(BSTree t, int val) {
	if (t == NULL) {
		BSTree a = malloc(sizeof(*a));
		a->value = val; 
		a->left = NULL;
		a->right = NULL; 
		return a;
	}
	
	if (val < t->value) {
		t->left = BSTreeInsert(t->left, val);
	}

	else if (val > t->value) {
		t->right = BSTreeInsert(t->right, val);
	}

	return t;
}

