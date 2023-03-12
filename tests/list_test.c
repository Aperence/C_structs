#include "list.h"
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
    list_t *list = list_new();

    int x = 5;
    int y = 3;
    int z = 8;

    list_add(list, &x);
    list_add(list, &y);
    list_add(list, &z);
    list_add(list, &x);

    list_remove(list);

    list_set(list, -1, &x);

    printf("Found : %d\n",  *((int *) list_get(list, 0)));
    printf("Found : %d\n",  *((int *) list_get(list, 1)));
    printf("Found : %d\n",  *((int *) list_get(list, 2)));
    printf("Size : %d\n", list_size(list));

    int not = 4;
    if (!list_contains(list, &not, eq)) printf("Not in list\n");

    list_delete(list);

    return 0;
}
