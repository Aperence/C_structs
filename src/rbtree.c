#include "rbtree.h"

void flip_colors(rbnode_t *n){
    n->color = RED;
    n->left->color = BLACK;
    n->right->color = BLACK;
}

int is_red(rbnode_t *n){
    if (!n) return 0;
    return n->color == RED;
}

rbnode_t *rotate_left(rbnode_t *n){
    rbnode_t *temp = n->right;
    n->right = temp->left;
    temp->left = n;
    return temp;
}

rbnode_t *rotate_right(rbnode_t *n){
    rbnode_t *temp = n->left;
    n->left = temp->right;
    temp->right = n;
    return temp;
}

rbnode_t *init_node(void *key, void *value){
    rbnode_t *n = malloc(sizeof(rbnode_t));
    if (!n) return NULL;
    n->color = RED;
    n->key = key;
    n->value = value;
    n->right = NULL;
    n->left = NULL;
    return n;
}

rbnode_t *add(rbnode_t *n, int (*compare)(void *, void *), void *key, void *value, int *modified){
    if (!n){
        rbnode_t *new = init_node(key, value);
        if (!new) return NULL;
        return new;
    }  
    int cmp = compare(n->key, key);
    if (cmp == 0){
        *modified = 0;
        n->value = value;
        return n;
    }
    else if (cmp > 0){
        n->left = add(n->left, compare, key, value, modified);
        if (!n->left) return NULL;
    }
    else{
        n->right = add(n->right, compare, key, value, modified);
        if (!n->right) return NULL;
    }

    // if right is red and left is not red, rotate left
    if (is_red(n->right) && !is_red(n->left)) n = rotate_left(n);
    // if left is red and left-left is red, rotate right
    if (is_red(n->left) && is_red(n->left->left)) n = rotate_right(n);
    // if both childs are red, make them black and make this node red (flip colors)
    if (is_red(n->right) && is_red(n->left)) flip_colors(n);

    return n;
}

rbtree_t *rbtree_new(int (*compare)(void *, void *)){
    rbtree_t *tree = malloc(sizeof(rbtree_t));
    tree->compare = compare;
    tree->size = 0;
    tree->root = NULL;
    return tree;
}

int rbtree_add(rbtree_t *tree, void *key, void *value){
    int modified = 1;
    tree->root = add(tree->root, tree->compare, key, value, &modified);
    if (!tree->root) return -1;
    tree->root->color = BLACK;
    if (modified) tree->size++;
    return 0;
}

void *node_get(rbnode_t *n, int (*compare)(void *, void *), void *key){
    if (!n) return NULL;
    int cmp = compare(n->key, key);
    if (cmp == 0) return n->value;
    if (cmp < 0) return node_get(n->right, compare, key);
    return node_get(n->left, compare, key);
}

void *rbtree_get(rbtree_t *tree, void *key){
    return node_get(tree->root, tree->compare, key);
}

int rbtree_size(rbtree_t *tree){
    return tree->size;
}

void node_delete(rbnode_t *n){
    if (!n) return;
    node_delete(n->left);
    node_delete(n->right);
    free(n);
}

void rbtree_delete(rbtree_t *tree){
    node_delete(tree->root);
    free(tree);
}