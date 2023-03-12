#include "list.h"

int max(int i, int j){
    return i > j ? i : j;
}

list_t *list_new(){
    list_t *new = malloc(sizeof(list_t));
    new->nb_elems = 0;
    new->size = 10;
    new->array = malloc(sizeof(void *) * new->size);
    return new;
}

int list_resize(list_t *list, uint32_t size){
    void **new_array = malloc((size) * sizeof(void *));
    if (!new_array) return -1;
    for (int i = 0; i < list->nb_elems; i++){
        new_array[i] = list->array[i];
    }
    free(list->array);
    list->size = size;
    list->array = new_array;
    return 0;
}

int list_add(list_t *list, void *value){
    if (list->size == list->nb_elems){
        if (list_resize(list, list->size*2) == -1) return -1;
    }
    list->array[list->nb_elems++] = value;
    return 0;
}

int list_contains(list_t *list, void *value, int (*equals)(void *, void *)){
    for (int i = 0; i < list->nb_elems; i++){
        if (equals(list->array[i], value)) return 1;
    }
    return 0;
}

void list_remove(list_t *list){
    if (list->nb_elems > 0) list->nb_elems--;
}

void *list_get(list_t *list, int32_t index){
    if (index >= list->nb_elems) return NULL;
    if (index < 0){
        index = list->nb_elems + index;
        if (index < 0) return NULL;
        return list->array[index];
    }
    return list->array[index];
}

void *list_set(list_t *list, int32_t index, void *value){
    if (index >= 0 && index >= list->size){
        if (list_resize(list, 2*index) == -1) return NULL;
    }
    if (index < 0) index = list->nb_elems + index;
    list->array[index] = value;
    list->nb_elems = max(list->nb_elems, index+1);
}

int list_capacity(list_t *list){
    return list->size;
}

int list_size(list_t *list){
    return list->nb_elems;
}

void list_delete(list_t *list){
    free(list->array);
    free(list);
}