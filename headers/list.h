#include <stdint.h>
#include <stdlib.h>

typedef struct list{
    void **array;
    uint32_t size;
    uint32_t nb_elems;

}list_t;

list_t *list_new();

int list_resize(list_t *list, uint32_t size);

int list_add(list_t *list, void *value);

void list_remove(list_t *list);

int list_contains(list_t *list, void *value, int (*equals)(void *, void *));

void *list_get(list_t *list, int32_t index);

void *list_set(list_t *list, int32_t index, void *value);

int list_capacity(list_t *list);

int list_size(list_t *list);

void list_delete(list_t *list);