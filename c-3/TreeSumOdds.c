
#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

int TreeSumOdds(Tree t) {
	if (t == NULL) {
		return 0;
	}

	if (t->value % 2 == 1) {
		return t->value + TreeSumOdds(t->right) + TreeSumOdds(t->left);
	}
	else {
		return TreeSumOdds(t->left) + TreeSumOdds(t->right);
	}
}

