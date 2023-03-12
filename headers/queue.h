#include <stdint.h>
#include <stdlib.h>

typedef struct queue{
    void **array;
    uint32_t size;
    uint32_t nb_elems;
    uint32_t start;
    uint32_t end;

}queue_t;

queue_t *queue_new();

int queue_empty(queue_t *queue);

int queue_enqueue(queue_t *queue, void *value);

void *queue_dequeue(queue_t *queue);

int queue_size(queue_t *queue);

void queue_delete(queue_t *queue);

