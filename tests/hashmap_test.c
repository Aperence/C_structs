#include "priority_queue.h"
#include "hashmap.h"
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
    hashmap_t *map = hashmap_new(10, hash, eq);

    int x = 5;
    int y = 3;
    int z = 8;

    hashmap_add(map, &x, &x);
    hashmap_add(map, &y, &y);
    hashmap_add(map, &z, &z);
    hashmap_add(map, &x, &z);

    printf("Found : %d\n", *((int *) hashmap_get(map, &x)));
    printf("Found : %d\n", *((int *) hashmap_get(map, &y)));
    printf("Found : %d\n", *((int *) hashmap_get(map, &z)));


    int not = 4;
    if (!hashmap_get(map, &not)) printf("Not in map\n");

    hashmap_delete(map);

    return 0;
}
