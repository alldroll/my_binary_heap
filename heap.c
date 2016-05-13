#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "heap.h"

typedef struct {
    size_t size;
    size_t capacity;
    SequenceT* data;
} HeapImplT;

#define GROWTH_FACTOR 2
#define INITIAL_CAPACITY 10
#define INVALID_NODE -1 /* TODO use - infinity */

#define LEFT_CHILD(index) (index << 1) + 1
#define RIGHT_CHILD(index) LEFT_CHILD(index) + 1
#define PARENT(index) (index - 1) >> 1

inline static void swap(SequenceT* a, SequenceT* b) {
    SequenceT c = *a;
    *a = *b;
    *b = c;
}

static int allocate_policy(HeapImplT* heap) {
    assert(heap != NULL);

    if (heap->capacity == 0) {
        heap->data = (SequenceT*) malloc(sizeof(SequenceT) * INITIAL_CAPACITY);
        heap->capacity = INITIAL_CAPACITY;
    }

    if (heap->data == NULL) {
        return 0;
    }

    if (heap->size == heap->capacity) {
        heap->capacity *= GROWTH_FACTOR;
        heap->data = realloc(heap->data, sizeof(SequenceT) * heap->capacity);
    }

    /* is it right? */
    if (heap->capacity > INITIAL_CAPACITY &&
        heap->capacity >= (heap->size * GROWTH_FACTOR * GROWTH_FACTOR)
    ) {
        heap->capacity /= GROWTH_FACTOR;
        heap->data = realloc(heap->data, sizeof(SequenceT) * heap->capacity);
    }

    return 1;
}

HeapT* create_heap_from(SequenceT* arr, size_t size) {
    if (arr == NULL) {
        return NULL;
    }

    HeapImplT* heap = (HeapImplT*) malloc(sizeof(HeapImplT));
    if (heap == NULL) {
        return NULL;
    }

    heap->data = (SequenceT*) malloc(sizeof(SequenceT) * size);
    if (heap->data == NULL) {
        free(heap);
        return NULL;
    }

    memcpy(heap->data, arr, size * sizeof(SequenceT));
    heap->capacity = size;
    heap->size = size;
    return (HeapT*) heap;
}

HeapT* create_heap() {
    HeapImplT* heap = (HeapImplT*) malloc(sizeof(HeapImplT));
    if (heap == NULL) {
        return NULL;
    }

    heap->data = NULL;
    heap->size = 0;
    heap->capacity = 0;
    if (!allocate_policy(heap)) {
        free(heap);
        return NULL;
    }

    return (HeapT*) heap;
}

void destroy_heap(HeapT* h) {
    if (h == NULL) {
        return;
    }

    HeapImplT* heap = (HeapImplT*) h;
    if (heap->data != NULL) {
        free(heap->data);
    }

    free(heap);
}

int get_heap_size(HeapT* h) {
    if (h == NULL) {
        return - 1;
    }

    HeapImplT* heap = (HeapImplT*) h;
    return heap->size;
}

SequenceT* get_heap_data(HeapT* h) {
    if (h == NULL) {
        return NULL;
    }

    HeapImplT* heap = (HeapImplT*) h;
    return heap->data;
}

void max_heapify(HeapT* h, size_t index) {
    assert(h != NULL);

    HeapImplT* heap = (HeapImplT*) h;
    size_t largest_index, left_index, right_index;

    /* loop way */
    while (1) {
        left_index = LEFT_CHILD(index);
        right_index = RIGHT_CHILD(index);
        largest_index = index;

        if (heap->size > left_index &&
            heap->data[left_index] > heap->data[largest_index]
        ) {
            largest_index = left_index;
        }

        if (heap->size > right_index &&
            heap->data[right_index] > heap->data[largest_index]
        ) {
            largest_index = right_index;
        }

        if (largest_index == index) {
            break;
        }

        swap(&heap->data[largest_index], &heap->data[index]);
        index = largest_index;
    }
}

/* rec way */
void min_heapify(HeapT* h, size_t index) {
    assert(h != NULL);

    HeapImplT* heap = (HeapImplT*) h;
    size_t left_index = LEFT_CHILD(index);
    size_t right_index = RIGHT_CHILD(index);
    size_t lowest_index = index;

    if (heap->size > left_index &&
        heap->data[left_index] < heap->data[lowest_index]
    ) {
        lowest_index = left_index;
    }

    if (heap->size > right_index &&
        heap->data[right_index] < heap->data[lowest_index]
    ) {
        lowest_index = right_index;
    }

    if (lowest_index != index) {
        swap(&heap->data[lowest_index], &heap->data[index]);
        max_heapify(h, lowest_index);
    }
}

void build_max_heap(HeapT* h) {
    assert(h != NULL);

    HeapImplT* heap = (HeapImplT*) h;
    int index = PARENT(heap->size - 1);
    for (; index >= 0; --index) {
        max_heapify(h, index);
    }
}

void build_min_heap(HeapT* h) {
    assert(h != NULL);

    HeapImplT* heap = (HeapImplT*) h;
    int index = PARENT(heap->size - 1);
    for (; index >= 0; --index) {
        min_heapify(h, index);
    }
}

void heapsort(SequenceT* arr, size_t size) {
    if (arr == NULL || size <= 1) {
        return;
    }

    HeapT* h = create_heap_from(arr, size);
    HeapImplT* heap = (HeapImplT*) h;
    assert(h != NULL);

    build_max_heap(h);
    size_t index = size - 1;
    for (; index > 0; --index) {
        swap(&heap->data[index], &heap->data[0]);
        --heap->size;
        max_heapify(h, 0);
    }

    memcpy(arr, heap->data, size * sizeof(SequenceT));
    destroy_heap(h);
}

SequenceT heap_maximum(HeapT* h) {
    HeapImplT* heap = (HeapImplT*) h;
    assert(heap != NULL && heap->size != 0);
    return heap->data[0];
}

SequenceT heap_extract_max(HeapT* h) {
    HeapImplT* heap = (HeapImplT*) h;
    assert(heap != NULL && heap->size != 0);

    SequenceT max = heap_maximum(h);
    heap->data[0] = heap->data[heap->size - 1];
    --heap->size;
    allocate_policy(heap);
    max_heapify(h, 0);
    return max;
}

void heap_increase_key(HeapT* h, size_t index, SequenceT key) {
    HeapImplT* heap = (HeapImplT*) h;
    assert(heap != NULL && heap->size > index);
    assert(key > heap->data[index]);

    heap->data[index] = key;
    size_t parent_index = PARENT(index);
    while (index > 0 && heap->data[parent_index] < heap->data[index]) {
        swap(&heap->data[index], &heap->data[parent_index]);
        index = parent_index;
    }
}

void max_heap_insert(HeapT* h, SequenceT key) {
    assert(h != NULL);

    HeapImplT* heap = (HeapImplT*) h;
    allocate_policy(heap);
    ++heap->size;
    heap->data[heap->size - 1] = INVALID_NODE;
    heap_increase_key(h, heap->size - 1, key);
}
