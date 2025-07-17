#ifndef PQUEUE_H
#define PQUEUE_H

#include "heap.h"

typedef Heap PQueue;

#define pqueue_create heap_create
#define pqueue_destroy heap_destroy


#define pqueue_insert heap_insert
#define pqueue_extract heap_extract

#define pqueue_peek(pqueue) ((pqueue)->tree[0] == NULL ? NULL : (pqueue)->tree[0])
#define pqueue_size(pqueue) ((pqueue)->size)

#endif
