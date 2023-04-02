#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

int TreeHeight(Tree t) {
    if (t == NULL) {
        return -1;
    } else {
        int l = TreeHeight(t->left);
        int r = TreeHeight(t->right);
        if (l > r) {
            return 1 + l;
        }
        else { 
            return 1 + r;
        }
    }
    return 0;
}


