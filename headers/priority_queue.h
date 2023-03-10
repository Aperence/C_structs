#include <stdlib.h>
#include <stdint.h>

typedef struct prio_queue{
    void **array;
    uint32_t size;
    int (*compare)(void *, void *);
    uint32_t nb_elems;

}prio_queue_t;

prio_queue_t *prio_new(int size, int (*compare)(void *, void *));

int prio_add(prio_queue_t *pq, void *item);

int prio_size(prio_queue_t *pq);

void *prio_pop(prio_queue_t *pq);

void *prio_top(prio_queue_t *pq);

void *prio_delete(prio_queue_t *pq);