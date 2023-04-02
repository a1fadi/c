int BSTreeCountGreater(BSTree t, int val) { 
    if (t == NULL) {
        return 0;
    }
    if (val >= t->value) {
        return BSTreeCountGreater(t->right, val);
    }
    else {
        return 1 + BSTreeCountGreater(t->right) + BSTreeCountGreater(t->left);
    }
}