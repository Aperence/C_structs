#include "hashset.h"
#include <stdlib.h>
#include <string.h>

typedef enum err{
    MALLOC_FAILED,
    ALREADY_IN,
    OK
}err_t;

hashset_t *hashset_new(uint32_t size, int (*hash)(void *), int (*equals)(void *, void *)){
    hashset_t *new = malloc(sizeof(hashset_t));
    new->lists = malloc(size * sizeof(set_list_t));
    if (!new->lists) return NULL;
    for (int i = 0; i < size; i++){
        set_list_t *list = &new->lists[i];
        list->array = malloc(10*sizeof(void *));
        if (!list->array) return NULL;
        list->size = 10;
        list->nb_elems = 0;
    }
    new->size = size;
    new->nb_elems = 0;
    new->hash = hash;
    new->equals = equals;
    return new;
}

int set_hashlist_resize(set_list_t *list){
    void **new_array = malloc((list->size*2) * sizeof(void *));
    if (!new_array) return -1;
    for (int i = 0; i < list->nb_elems; i++){
        new_array[i] = list->array[i];
    }
    free(list->array);
    list->size *= 2;
    list->array = new_array;
    return 0;
}

err_t set_list_add(set_list_t *list, void *value, int (*equals)(void *, void *)){
    for (int i = 0; i < list->nb_elems; i++){
        void *v = list->array[i];
        if (equals(value, v)) return ALREADY_IN;
    }
    if (list->size == list->nb_elems){
        if (set_hashlist_resize(list) == -1) return MALLOC_FAILED;
    }
    list->array[list->nb_elems++] = value;
    return OK;
}

int hashset_add(hashset_t *set, void *value){
    int hashed = set->hash(value);
    hashed = hashed % set->size;
    err_t err = set_list_add(&set->lists[hashed], value, set->equals);
    if (err == MALLOC_FAILED) return -1;
    if (err != ALREADY_IN) set->nb_elems++;
    return 0;
}

int set_list_contains(set_list_t *list, void *value, int (*equals)(void *, void *)){
    for (int i = 0; i < list->nb_elems; i++){
        if (equals(list->array[i], value)) return 1;
    }
    return 0;
}

int hashset_contains(hashset_t *set, void *key){
    int hashed = set->hash(key);
    hashed = hashed % set->size;
    return set_list_contains(&set->lists[hashed], key, set->equals);
}

int hashset_size(hashset_t *set){
    return set->nb_elems;
}

void hashset_delete(hashset_t *set){
    for (int i = 0; i < set->size; i++) free(set->lists[i].array);
    free(set->lists);
    free(set);
}