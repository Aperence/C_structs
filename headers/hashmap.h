#include <stdint.h>

typedef struct pair{
    void *key;
    void *value;

}pair_t;

typedef struct table_list{
    pair_t **array;
    uint32_t size;
    uint32_t nb_elems;

}table_list_t;

typedef struct hashmap{
    table_list_t *lists;
    uint32_t size;
    uint32_t nb_elems;
    int (*hash)(void *);
    int (*equals)(void *, void *);

}hashmap_t;

hashmap_t *hashmap_new(uint32_t size, int (*hash)(void *), int (*equals)(void *, void *));

int hashmap_add(hashmap_t *map, void *key, void *value);

void *hashmap_get(hashmap_t *map, void *key);

int hashmap_size(hashmap_t *map);

void hashmap_delete(hashmap_t *map);