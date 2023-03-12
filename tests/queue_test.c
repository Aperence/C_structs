#include "queue.h"
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
    queue_t *queue = queue_new();

    int x = 5;
    int y = 3;
    int z = 8;

    queue_enqueue(queue, &x);
    queue_dequeue(queue);
    queue_enqueue(queue, &y);
    queue_enqueue(queue, &z);
    queue_enqueue(queue, &x);

    printf("Found : %d\n",  *((int *) queue_dequeue(queue)));
    printf("Found : %d\n",  *((int *) queue_dequeue(queue)));
    printf("Found : %d\n",  *((int *) queue_dequeue(queue)));
    printf("Size : %d\n", queue_size(queue));

    queue_dequeue(queue);

    printf("Size : %d\n", queue_size(queue));

    if (!queue_dequeue(queue)) printf("NULL value\n");

    queue_delete(queue);

    return 0;
}
