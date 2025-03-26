#include "heap.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define heap_parent(npos) ((int)(((npos) - 1) / 2))
#define heap_left(npos) (((npos * 2) + 1))
#define heap_right(npos) (((npos * 2) + 2))

void heap_create(Heap* heap, int (*match)(const void* key1, const void* key2),
    void (*destroy)(void* data))
{
    heap->destroy = destroy;
    heap->match = match;
    heap->size = 0;
    heap->tree = NULL;
}
void heap_destroy(Heap* heap)
{
    if (heap_size(heap) == 0) {
        return;
    }

    if (heap->destroy) {
        for (size_t i = 0; i < heap_size(heap); i++) {
            heap->destroy(heap->tree[i]);
        }
    }
    heap->destroy(heap->tree);
    memset(heap, 0, sizeof(Heap));
}
int heap_insert(Heap* heap, const void* data)
{
    void* temp;
    int ipos, ppos;

    if ((temp = realloc(heap->tree, (heap_size(heap) + 1) * sizeof(void*))) == NULL) {
        return -1;
    } else {
        heap->tree = temp;
    }

    heap->tree[heap_size(heap)] = (void*)data;

    ipos = heap_size(heap);
    ppos = heap_parent(ipos);

    while (ipos > 0 && heap->match(heap->tree[ppos], heap->tree[ipos]) < 0) {
        temp = heap->tree[ppos];
        heap->tree[ppos] = heap->tree[ipos];
        heap->tree[ipos] = temp;

        ipos = ppos;
        ppos = heap_parent(ppos);
    }

    heap->size++;
    return 0;
}
int heap_extract(Heap* heap, void** data)
{
    void* temp;
    void* last_saved_element;
    if (heap_size(heap) == 0) {
        return -1;
    }

    *data = heap->tree[0];
    last_saved_element = heap->tree[heap_size(heap) - 1];

    if (heap_size(heap) - 1 > 0) {
        if ((temp = realloc(heap->tree, (heap_size(heap) - 1) * sizeof(void*))) == NULL) {
            return -1;
        } else {
            heap->tree = temp;
        }
        heap->size--;
    } else {
        free(heap->tree);
        heap->tree = NULL;
        heap->size = 0;
        return 0;
    }

    heap->tree[0] = last_saved_element;
    int rpos, lpos, ipos, mpos;

    ipos = 0;
    lpos = heap_left(ipos);
    rpos = heap_right(ipos);

    while (true) {
        lpos = heap_left(ipos);
        rpos = heap_right(ipos);
        if (lpos < (int)heap_size(heap) && heap->match(heap->tree[lpos], heap->tree[ipos]) > 0) {
            mpos = lpos;
        } else {
            mpos = ipos;
        }

        if (rpos < (int)heap_size(heap) && heap->match(heap->tree[rpos], heap->tree[mpos]) > 0) {
            mpos = rpos;
        }

        if (mpos == ipos) {
            break;
        } else {
            temp = heap->tree[mpos];
            heap->tree[mpos] = heap->tree[ipos];
            heap->tree[ipos] = temp;
        }
        ipos = mpos;
    }

    return 0;
}