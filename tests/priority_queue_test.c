#include "priority_queue.h"
#include <stdio.h>

int compare(void *x, void *y){
    return *((int *)x) - *((int *)y);
}

int main(int argc, char const *argv[])
{
    prio_queue_t *pq = prio_new(3, compare);

    int x = 5;
    int y = 3;
    int z = 8;

    prio_add(pq, &x);
    prio_add(pq, &y);
    prio_add(pq, &z);
    prio_add(pq, &x);

    printf("Top : %d\n", *((int *)prio_top(pq)));
    printf("Pop : %d\n", *((int *)prio_pop(pq)));
    printf("Pop : %d\n", *((int *)prio_pop(pq)));
    printf("Pop : %d\n", *((int *)prio_pop(pq)));
    printf("Pop : %d\n", *((int *)prio_pop(pq)));

    void *ret = prio_pop(pq);

    if (!ret) printf("NULL value\n");

    prio_delete(pq);

    return 0;
}
