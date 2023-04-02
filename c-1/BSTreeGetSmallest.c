
#include "BSTree.h"
#include <stdio.h>
#include <stdlib.h>

BSTree BSTreeGetSmallest(BSTree t) {
	if (t == NULL) {
		return NULL; 
	}
	if (t->left == NULL && t->right != NULL) {
		return t;
	}
	else if (t->left != NULL) {
		t = BSTreeGetSmallest(t->left);
	}
	else if (t->left == NULL && t->right == NULL) {
		return t;
	}
	return t;
}

