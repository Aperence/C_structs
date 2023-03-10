#include <stdint.h>
#include <stdlib.h>

enum color{
    RED,
    BLACK
};

typedef struct rbnode{
    void *key;
    void *value;
    struct rbnode *left;
    struct rbnode *right;
    enum color color;

}rbnode_t;

typedef struct rbtree{
    rbnode_t *root;
    uint32_t size;
    int (*compare)(void *, void *);

}rbtree_t;

rbtree_t *rbtree_new(int (*compare)(void *, void *));

int rbtree_add(rbtree_t *tree, void *key, void *value);

void *rbtree_get(rbtree_t *tree, void *key);

int rbtree_size(rbtree_t *tree);

void rbtree_delete(rbtree_t *tree);
