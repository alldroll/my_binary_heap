#ifndef __HEAP__
#define __HEAP__

#include <stddef.h>

typedef int SequenceT;
typedef void* HeapT;

/**
 * create empty heap
 */
extern HeapT* create_heap();

/*
 * create heap and copy arr to heap (is not min(max)-heap)
 */
extern HeapT* create_heap_from(const SequenceT* arr, size_t size);

/**
 * destroy heap and free all allocated memory
 */
extern void destroy_heap(HeapT* heap);

/**/
extern int get_heap_size(HeapT* heap);

/**
 * get heap data as array
 */
extern SequenceT* get_heap_data(HeapT* heap);

/**
 * restore max-heap property from index
 */
extern void max_heapify(HeapT* heap, size_t index);

/**
 * restore min-heap property from index
 */
extern void min_heapify(HeapT* heap, size_t index);

/**
 * build heap with max-heap property
 */
extern void build_max_heap(HeapT* heap);

/**
 * build heap with min-heap property
 */
extern void build_min_heap(HeapT* heap);

/**
 * sort array with given size in desc order
 */
extern void heapsort(SequenceT* arr, size_t size);

/**
 * get maximum key of max-heap
 */
extern SequenceT heap_maximum(HeapT* heap);

/**
 * extract maximum key of max-heap
 */
extern SequenceT heap_extract_max(HeapT* heap);

/**
 * increase element at index by given key
 */
extern void heap_increase_key(HeapT* heap, size_t index, SequenceT key);

/**
 * insert key
 */
extern void max_heap_insert(HeapT* heap, SequenceT key);

#endif
