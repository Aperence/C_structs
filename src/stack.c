#include "stack.h"

stack_t *stack_new(){
    stack_t *new = malloc(sizeof(stack_t));
    new->nb_elems = 0;
    new->size = 10;
    new->array = malloc(sizeof(void *) * new->size);
    return new;
}

int stack_empty(stack_t *stack){
    return stack->nb_elems == 0;
}

int stack_resize(stack_t *stack, uint32_t size){
    void **new_array = malloc((size) * sizeof(void *));
    if (!new_array) return -1;
    for (int i = 0; i < stack->nb_elems; i++){
        new_array[i] = stack->array[i];
    }
    free(stack->array);
    stack->size = size;
    stack->array = new_array;
    return 0;
}

int stack_push(stack_t *stack, void *value){
    if (stack->size == stack->nb_elems){
        if (stack_resize(stack, stack->size*2) == -1) return -1;
    }
    stack->array[stack->nb_elems++] = value;
    return 0;
}

void *stack_pop(stack_t *stack){
    if (stack_empty(stack)) return NULL;
    void *ret = stack->array[stack->nb_elems-1];
    stack->nb_elems--;
    return ret;
}

int stack_size(stack_t *stack){
    return stack->nb_elems;
}

void stack_delete(stack_t *stack){
    free(stack->array);
    free(stack);
}