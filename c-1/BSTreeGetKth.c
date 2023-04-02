
#include <stdlib.h>
#include <stdio.h>
#include "BSTree.h"

int BSTreeSize(BSTree t);
int BSTreeGetKth(BSTree t, int k) {
	int size = BSTreeSize(t->left);
	if (k == size) {
		return t->value;
	}
	else if (k < size) {
		return BSTreeGetKth(t->left, k);
	}
	else {
		return BSTreeGetKth(t->right, k - size - 1);
	}
}

int BSTreeSize(BSTree t) {
	if (t == NULL) {
		return 0;
	}
	else {
		return 1 + BSTreeSize(t->left) + BSTreeSize(t->right);
	}
}

