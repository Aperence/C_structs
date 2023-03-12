#include "stack.h"
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
    stack_t *stack = stack_new();

    int x = 5;
    int y = 3;
    int z = 8;

    stack_push(stack, &x);
    stack_push(stack, &y);
    stack_pop(stack);
    stack_push(stack, &z);
    stack_push(stack, &x);

    printf("Found : %d\n",  *((int *) stack_pop(stack)));
    printf("Found : %d\n",  *((int *) stack_pop(stack)));
    printf("Found : %d\n",  *((int *) stack_pop(stack)));
    printf("Size : %d\n", stack_size(stack));

    stack_pop(stack);

    printf("Size : %d\n", stack_size(stack));

    if (!stack_pop(stack)) printf("NULL value\n");

    stack_delete(stack);

    return 0;
}
