#include <stddef.h>
int create_maxheap(float *num, size_t num_size, float **max_heap);
int create_minheap(float *num, size_t num_size, float **min_heap);
int insert_maxheap(float **max_heap, size_t *heap_size, float value);
int insert_minheap(float **min_heap, size_t *heap_size, float value);
int update_maxheap(float **max_heap, size_t heap_size, size_t target, float value);
int update_minheap(float **min_heap, size_t heap_size, size_t target, float value);
int delete_maxheap(float **max_heap, size_t *heap_size, size_t target);
int delete_minheap(float **min_heap, size_t *heap_size, size_t target);
float extract_max(float **max_heap, size_t *heap_size);
float extract_min(float **min_heap, size_t *heap_size);