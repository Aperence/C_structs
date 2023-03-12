#include "queue.h"

queue_t *queue_new(){
    queue_t *new = malloc(sizeof(queue_t));
    new->nb_elems = 0;
    new->size = 10;
    new->start = 0;
    new->end = 0;
    new->array = malloc(sizeof(void *) * new->size);
    return new;
}

int queue_empty(queue_t *queue){
    return queue->nb_elems == 0;
}

int queue_resize(queue_t *queue, uint32_t size){
    void **new_array = malloc((size) * sizeof(void *));
    if (!new_array) return -1;
    for (int i = 0; i < queue->nb_elems; i++){
        int index = (i + queue->start) % queue->size;
        new_array[i] = queue->array[index];
    }
    free(queue->array);
    queue->size = size;
    queue->start = 0;
    queue->end = queue->nb_elems;
    queue->array = new_array;
    return 0;
}

int queue_enqueue(queue_t *queue, void *value){
    if (queue->size == queue->nb_elems){
        if (queue_resize(queue, queue->size*2) == -1) return -1;
    }
    queue->array[queue->end] = value;
    queue->end = (queue->end + 1) % queue->size;
    queue->nb_elems++;
    return 0;
}

void *queue_dequeue(queue_t *queue){
    if (queue_empty(queue)) return NULL;
    void *ret = queue->array[queue->start];
    queue->start = (queue->start + 1) % queue->size;
    queue->nb_elems--;
    return ret;
}

int queue_size(queue_t *queue){
    return queue->nb_elems;
}

void queue_delete(queue_t *queue){
    free(queue->array);
    free(queue);
}