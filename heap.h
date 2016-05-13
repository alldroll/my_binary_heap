#ifndef __HEAP__
#define __HEAP__

#include <stddef.h>

typedef int SequenceT;
typedef void* HeapT;

extern HeapT* create_heap();
extern HeapT* create_heap_from(const SequenceT* arr, size_t size);
extern void destroy_heap(HeapT* heap);
extern int get_heap_size(HeapT* heap);
extern SequenceT* get_heap_data(HeapT* heap);
extern void max_heapify(HeapT* heap, size_t index);
extern void min_heapify(HeapT* heap, size_t index);
extern void build_max_heap(HeapT* heap);
extern void build_max_heap(HeapT* heap);
extern void heapsort(SequenceT* arr, size_t size);
extern SequenceT heap_maximum(HeapT* heap);
extern SequenceT heap_extract_max(HeapT* heap);
extern void heap_increase_key(HeapT* heap, size_t index, SequenceT key);
extern void max_heap_insert(HeapT* heap, SequenceT key);

#endif
