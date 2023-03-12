#include <stdint.h>


typedef struct set_list{
    void **array;
    uint32_t size;
    uint32_t nb_elems;

}set_list_t;

typedef struct hashset{
    set_list_t *lists;
    uint32_t size;
    uint32_t nb_elems;
    int (*hash)(void *);
    int (*equals)(void *, void *);

}hashset_t;

hashset_t *hashset_new(uint32_t size, int (*hash)(void *), int (*equals)(void *, void *));

int hashset_add(hashset_t *set, void *value);

int hashset_contains(hashset_t *set, void *value);

int hashset_size(hashset_t *map);

void hashset_delete(hashset_t *set);