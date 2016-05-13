#include <stdio.h>
#include <assert.h>
#include "heap.h"

#define HEAP_ASSERT_DATA_EQUALS(expected, h)     \
{                                                \
    assert(h != NULL);                           \
    int size = get_heap_size(h);                 \
    size_t i = 0;                                \
    SequenceT* data = get_heap_data(h);          \
    for (; i < size; ++i) {                      \
        assert(expected[i] == data[i]);          \
    }                                            \
}

int main() {
    /* 6_2_1, 6_2_5 */
    {
        SequenceT arr[14] = {27, 17, 3, 16, 13, 10, 1, 5, 7, 12, 4, 8, 9, 0};
        SequenceT expected[14] = {27, 17, 10, 16, 13, 9, 1, 5, 7, 12, 4, 8, 3, 0};
        HeapT* heap = create_heap_from((SequenceT*) &arr, 14);
        max_heapify(heap, 2);

        HEAP_ASSERT_DATA_EQUALS(expected, heap);

        destroy_heap(heap);
    }

    /* 6_2_2 */
    {
        SequenceT arr[5] = {2, 6, 3, 7, 5};
        SequenceT expected[5] = {2, 5, 3, 7, 6};
        HeapT* heap = create_heap_from((SequenceT*) &arr, 5);
        min_heapify(heap, 1);

        HEAP_ASSERT_DATA_EQUALS(expected, heap);

        destroy_heap(heap);
    }

    /* 6_3_1 */
    {
        SequenceT arr[10] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
        SequenceT expected[10] = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
        HeapT* heap = create_heap_from((SequenceT*) &arr, 10);
        build_max_heap(heap);

        HEAP_ASSERT_DATA_EQUALS(expected, heap);

        destroy_heap(heap);
    }

    {
        SequenceT arr[9] = {5, 13, 2, 25, 7, 17, 20, 8, 4};
        SequenceT expected[9] = {2, 4, 5, 7, 8, 13, 17, 20, 25};

        heapsort(arr, 9);
        size_t i = 0;
        for (; i < 9; ++i) {
            assert(expected[i] == arr[i]);
        }
    }

    {
        HeapT* heap = create_heap();

        max_heap_insert(heap, 1);
        max_heap_insert(heap, 5);
        max_heap_insert(heap, 3);

        SequenceT expected[3] = {5, 3, 1};
        size_t i = 0;
        SequenceT tmp;
        for (; i < 3; ++i) {
            tmp = heap_extract_max(heap);
            assert(expected[i] == tmp);
        }

        destroy_heap(heap);
    }

    {
        HeapT* heap = create_heap();

        size_t i = 0;
        for (; i < 1000; ++i) {
            max_heap_insert(heap, i);
        }


        SequenceT val;
        for (i = 0; i < 1000; ++i) {
            val = heap_extract_max(heap);
            assert(val == 999 - i);
        }

        destroy_heap(heap);
    }

    {
        HeapT* heap = create_heap();

        size_t i = 0;
        for (; i < 1000; ++i) {
            max_heap_insert(heap, 1000);
        }


        SequenceT tmp;
        for (i = 0; i < 1000; ++i) {
            tmp = heap_extract_max(heap);
            assert(1000 == tmp);
        }

        destroy_heap(heap);
    }

    {
        SequenceT arr[10] = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
        HeapT* heap = create_heap_from((SequenceT*) &arr, 10);
        heap_increase_key(heap, 8, 15);

        SequenceT expected[10] = {16, 15, 10, 14, 7, 9, 3, 2, 8, 1};
        HEAP_ASSERT_DATA_EQUALS(expected, heap);

        destroy_heap(heap);
    }

    printf("[OK] All test passed\n");

    return 0;
}
