#include "priority_queue.h"
#include "rbtree.h"
#include <stdio.h>

int compare(void *x, void *y){
    return *((int *)x) - *((int *)y);
}

int main(int argc, char const *argv[])
{
    rbtree_t *tree = rbtree_new(compare);

    int x = 5;
    int y = 3;
    int z = 8;

    rbtree_add(tree, &x, &x);
    rbtree_add(tree, &y, &y);
    rbtree_add(tree, &z, &z);
    rbtree_add(tree, &x, &z);

    printf("Found : %d\n", *((int *) rbtree_get(tree, &x)));
    printf("Found : %d\n", *((int *) rbtree_get(tree, &y)));
    printf("Found : %d\n", *((int *) rbtree_get(tree, &z)));


    int not = 4;
    if (!rbtree_get(tree, &not)) printf("Not in tree\n");

    rbtree_delete(tree);

    return 0;
}
