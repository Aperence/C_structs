#include <stdint.h>
#include <stdlib.h>

typedef struct stack{
    void **array;
    uint32_t size;
    uint32_t nb_elems;

}stack_t;

stack_t *stack_new();

int stack_empty(stack_t *stack);

int stack_push(stack_t *stack, void *value);

void *stack_pop(stack_t *stack);

int stack_size(stack_t *stack);

void stack_delete(stack_t *stack);

