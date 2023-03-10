#include "priority_queue.h"
#include <string.h>

prio_queue_t *prio_new(int size, int (*compare)(void *, void *)){
    prio_queue_t *pq = malloc(sizeof(prio_queue_t));
    pq->array = malloc((size+1) * sizeof(void *));
    pq->compare = compare;
    pq->size = size;
    pq->nb_elems = 0;
    return pq;
}

void swim(prio_queue_t *pq, int pos){
    if (pos <= 1) return;
    int parent = pos >> 1;
    void *parent_elem = pq->array[parent];
    void *elem = pq->array[pos];
    if (pq->compare(parent_elem, elem) < 0){
        pq->array[pos] = parent_elem;
        pq->array[parent] = elem;
        swim(pq, parent);
    }
}

void sink(prio_queue_t *pq, int pos){
    int left = pos*2;
    int right = pos*2+1;

    void *elem = pq->array[pos];
    int max_ind;
    void *max;
    if (left > pq->nb_elems) return;
    max = pq->array[left];
    max_ind = left;
    if (right <= pq->nb_elems && pq->compare(pq->array[right], max) > 0){
        max = pq->array[right];
        max_ind = right;
    }
    if (pq->compare(max, elem) > 1){
        pq->array[max_ind] = elem;
        pq->array[pos] = max;
        sink(pq, max_ind);
    }
}

int resize(prio_queue_t *pq){
    void **new_array = malloc((pq->size*2 + 1) * sizeof(void *));
    if (!new_array) return -1;
    memcpy(new_array, pq->array, sizeof(void *) * (pq->size+1));
    free(pq->array);
    pq->size *= 2;
    pq->array = new_array;
    return 0;
}

int prio_add(prio_queue_t *pq, void *item){
    if (pq->nb_elems == pq->size){
        int err = resize(pq);
        if (err != 0) return err;
    }

    pq->array[++pq->nb_elems] = item;
    swim(pq, pq->nb_elems);
}

int prio_size(prio_queue_t *pq){
    return pq->nb_elems;
}

void *prio_pop(prio_queue_t *pq){
    if (pq->nb_elems == 0) return NULL;
    void *ret = pq->array[1];
    pq->nb_elems--;
    if (pq->nb_elems != 0){
        pq->array[1] = pq->array[pq->nb_elems+1];
        sink(pq, 1);
    }
    return ret;
}

void *prio_top(prio_queue_t *pq){
    if (pq->nb_elems == 0) return NULL;
    return pq->array[1];
}

void *prio_delete(prio_queue_t *pq){
    free(pq->array);
    free(pq);
}