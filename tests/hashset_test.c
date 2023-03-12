#include "priority_queue.h"
#include "hashset.h"
#include <stdio.h>

int compare(void *x, void *y){
    return *((int *)x) - *((int *)y);
}

int eq(void *x, void *y){
    return *((int *)x) == *((int *)y);
}

int hash(void *x){
    return *((int *)x);
}

int main(int argc, char const *argv[])
{
    hashset_t *set = hashset_new(10, hash, eq);

    int x = 5;
    int y = 3;
    int z = 8;

    hashset_add(set, &x);
    hashset_add(set, &y);
    hashset_add(set, &z);
    hashset_add(set, &x);

    printf("Found : %d\n",  hashset_contains(set, &x));
    printf("Found : %d\n",  hashset_contains(set, &y));
    printf("Found : %d\n", hashset_contains(set, &z));
    printf("Size : %d\n", hashset_size(set));

    int not = 4;
    if (!hashset_contains(set, &not)) printf("Not in set\n");

    hashset_delete(set);

    return 0;
}
