#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

typedef enum err{
    MALLOC_FAILED,
    ALREADY_IN,
    OK
}err_t;

hashmap_t *hashmap_new(uint32_t size, int (*hash)(void *), int (*equals)(void *, void *)){
    hashmap_t *new = malloc(sizeof(hashmap_t));
    new->lists = malloc(size * sizeof(table_list_t));
    if (!new->lists) return NULL;
    for (int i = 0; i < size; i++){
        table_list_t *list = &new->lists[i];
        list->array = malloc(10*sizeof(pair_t *));
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

int hashlist_resize(table_list_t *list){
    pair_t **new_array = malloc((list->size*2) * sizeof(pair_t *));
    if (!new_array) return -1;
    for (int i = 0; i < list->nb_elems; i++){
        new_array[i] = list->array[i];
    }
    free(list->array);
    list->size *= 2;
    list->array = new_array;
    return 0;
}

err_t map_list_add(table_list_t *list, void *key, void *value, int (*equals)(void *, void *)){
    for (int i = 0; i < list->nb_elems; i++){
        pair_t *pair = list->array[i];
        if (equals(pair->key, key)){
            pair->value = value;
            return ALREADY_IN;
        }
    }
    if (list->size == list->nb_elems){
        if (hashlist_resize(list) == -1) return MALLOC_FAILED;
    }
    pair_t *new = malloc(sizeof(pair_t));
    if (!new) return MALLOC_FAILED;
    new->key = key;
    new->value = value;
    list->array[list->nb_elems++] = new;
    return OK;
}

int hashmap_add(hashmap_t *map, void *key, void *value){
    int hashed = map->hash(key);
    hashed = hashed % map->size;
    err_t err = map_list_add(&map->lists[hashed], key, value, map->equals);
    if (err == MALLOC_FAILED) return -1;
    if (err != ALREADY_IN) map->nb_elems++;
    return 0;
}

void *map_list_get(table_list_t *list, void *key, int (*equals)(void *, void *)){
    for (int i = 0; i < list->nb_elems; i++){
        pair_t *pair = list->array[i];
        if (equals(pair->key, key)) return pair->value;
    }
    return NULL;
}

void *hashmap_get(hashmap_t *map, void *key){
    int hashed = map->hash(key);
    hashed = hashed % map->size;
    return map_list_get(&map->lists[hashed], key, map->equals);
}

int hashmap_size(hashmap_t *map){
    return map->nb_elems;
}

void map_list_delete(table_list_t *list){
    for (int i = 0; i < list->nb_elems; i++){
        pair_t *pair = list->array[i];
        free(pair);
    }
    free(list->array);
}

void hashmap_delete(hashmap_t *map){
    for (int i = 0; i < map->size; i++){
        map_list_delete(&map->lists[i]);
    }
    free(map->lists);
    free(map);
}