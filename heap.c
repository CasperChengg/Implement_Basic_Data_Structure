#include "./headers/heap.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG 0
#define SUCCESS 0
#define NOT_EXIST -1
#define OUT_OF_RANGE -2
#define MEMROY_ALLOCATION_ERROR -3
void swap(float *x, float *y)
{
    float temp = *x;
    *x = *y;
    *y = temp;
}
int parent(float *heap, size_t heap_size, size_t target)
{
    // l_child is used to store the left child of the target
    size_t parent_node; 

    // Offseting the heap array by 1 would be easier to implement a heap
    parent_node = (target + 1) / 2; 
    if(parent_node < 1)
    {
        return NOT_EXIST;
    }
    else
    {
        // return the parent of the target without offsetting
        return parent_node - 1;
    }
}
int left_child(float *heap, size_t heap_size, size_t target)
{
    // l_child is used to store the left child of the target
    size_t l_child; 
    // Offseting the heap array by 1 would be easier to implement a heap
    // 2 * targe + 2 = 2 * (target + 1)
    l_child = 2 * target + 2; 
    if(l_child > heap_size)
    {
        return NOT_EXIST;
    }
    else
    {
        // return the right child of the target without offsetting
        return l_child - 1;
    }
}
int right_child(float *heap, size_t heap_size, size_t target)
{
    // r_child is used to store the right child of the target
    size_t r_child; 
    // Offseting the heap array by 1 would be easier to implement a heap
    // 2 * targe + 3 = 2 * (target + 1) + 1
    r_child = 2 * target + 3; 
    if(r_child > heap_size)
    {
        return NOT_EXIST;
    }
    else
    {
        // return the right child of the target without offsetting
        return r_child - 1;
    }
}
void max_heapify(float *max_heap, size_t heap_size, size_t target)
{
    int r_child, l_child;
    l_child = left_child(max_heap, heap_size, target);
    if(l_child == NOT_EXIST)
    {
        return;
    }
    r_child = right_child(max_heap, heap_size, target);
    if(r_child == NOT_EXIST)
    {
        if(max_heap[target] < max_heap[l_child])
        {
            swap(&max_heap[target], &max_heap[l_child]);
        }
    }
    else
    {
        if(max_heap[l_child] < max_heap[r_child])
        {
            if(max_heap[target] < max_heap[r_child])
            {
                swap(&max_heap[target], &max_heap[r_child]);
                max_heapify(max_heap, heap_size, r_child);
            }
        }
        else{
            if(max_heap[target] < max_heap[l_child])
            {
                swap(&max_heap[target], &max_heap[l_child]);
                max_heapify(max_heap, heap_size, l_child);
            }
        }
    }
}
void min_heapify(float *min_heap, size_t heap_size, size_t target)
{
    int r_child, l_child;
    l_child = left_child(min_heap, heap_size, target);
    if(l_child == NOT_EXIST)
    {
        return;
    }
    r_child = right_child(min_heap, heap_size, target);
    if(r_child == NOT_EXIST)
    {
        if(min_heap[target] > min_heap[l_child])
        {
            swap(&min_heap[target], &min_heap[l_child]);
        }
    }
    else
    {
        if(min_heap[l_child] <= min_heap[r_child])
        {
            if(min_heap[target] > min_heap[l_child])
            {
                swap(&min_heap[target], &min_heap[l_child]);
                min_heapify(min_heap, heap_size, l_child);
            }
        }
        else{
            if(min_heap[target] > min_heap[r_child])
            {
                swap(&min_heap[target], &min_heap[r_child]);
                min_heapify(min_heap, heap_size, r_child);
            }
        }
    }
}
int create_maxheap(float *num, size_t num_size, float **max_heap)
{
    *max_heap = calloc(num_size, sizeof(float));
    if((*max_heap) == NULL)
    {
        #ifdef DEBUG
            fprintf(stderr, "MEMORY ALLOCATION ERROR\n");  
        #endif
        return MEMROY_ALLOCATION_ERROR;
    }
    memcpy(*max_heap, num, num_size * sizeof(float));
    for(int target = num_size / 2; target >= 0; target--)
    {
        max_heapify(*max_heap, num_size, target);
    }
    return SUCCESS;
}
int create_minheap(float *num, size_t num_size, float **min_heap)
{
    *min_heap = calloc(num_size, sizeof(float));
    if((*min_heap) == NULL)
    {
        #ifdef DEBUG
            fprintf(stderr, "MEMORY ALLOCATION ERROR\n");  
        #endif
        return MEMROY_ALLOCATION_ERROR;
    }
    memcpy(*min_heap, num, num_size * sizeof(float));
    for(int target = num_size / 2; target >= 0; target--)
    {
        min_heapify(*min_heap, num_size, target);
    }
    return SUCCESS;
}
void increase_key_maxheap(float *max_heap, size_t heap_size, size_t target)
{
    size_t parent_node;
    parent_node = parent(max_heap, heap_size, target);
    if(parent_node == NOT_EXIST)
    {
        return;
    }
    if(max_heap[parent_node] < max_heap[target])
    {
        swap(&max_heap[parent_node], &max_heap[target]);
        increase_key_maxheap(max_heap, heap_size, parent_node);
    }
}
void increase_key_minheap(float *min_heap, size_t heap_size, size_t target)
{
    size_t parent_node;
    parent_node = parent(min_heap, heap_size, target);
    if(parent_node == NOT_EXIST)
    {
        return;
    }
    if(min_heap[parent_node] > min_heap[target])
    {
        swap(&min_heap[parent_node], &min_heap[target]);
        increase_key_minheap(min_heap, heap_size, parent_node);
    }
}
int insert_maxheap(float **max_heap, size_t *heap_size, float value)
{
    float *new_max_heap;
    (*heap_size) = (*heap_size) + 1;
    new_max_heap = (float*)realloc(*max_heap, sizeof(float) * (*heap_size));
    if(new_max_heap == NULL)
    {
        return MEMROY_ALLOCATION_ERROR;
    }
    *max_heap = new_max_heap;
    (*max_heap)[(*heap_size) - 1] = value;
    increase_key_maxheap(*max_heap, (*heap_size), (*heap_size) - 1);
    return SUCCESS;
}
int insert_minheap(float **min_heap, size_t *heap_size, float value)
{
    float *new_min_heap;
    (*heap_size) = (*heap_size) + 1;
    new_min_heap = (float*)realloc(*min_heap, sizeof(float) * (*heap_size));
    if(new_min_heap == NULL)
    {
        return MEMROY_ALLOCATION_ERROR;
    }
    *min_heap = new_min_heap;
    (*min_heap)[(*heap_size) - 1] = value;
    increase_key_minheap(*min_heap, (*heap_size), (*heap_size) - 1);
    return SUCCESS;
}
int update_maxheap(float **max_heap, size_t heap_size, size_t target, float value)
{
    if(target >= heap_size || target < 0)
    {
        #ifdef DEBUG
            fprintf(stderr, "index out of range : update_maxheap\n");
        #endif
        return OUT_OF_RANGE;
    }
    if((*max_heap)[target] < value)
    {
        (*max_heap)[target] = value;
        increase_key_maxheap(*max_heap, heap_size, target);
    }
    else
    {
        (*max_heap)[target] = value;
        max_heapify(*max_heap, heap_size, target);
    }
    return SUCCESS;
}
int update_minheap(float **min_heap, size_t heap_size, size_t target, float value)
{
    if(target >= heap_size || target < 0)
    {
        #ifdef DEBUG
            fprintf(stderr, "index out of range : update_minheap\n");
        #endif
        return OUT_OF_RANGE;
    }
    if((*min_heap)[target] > value)
    {
        (*min_heap)[target] = value;
        increase_key_minheap(*min_heap, heap_size, target);
    }
    else
    {
        (*min_heap)[target] = value;
        min_heapify(*min_heap, heap_size, target);
    }
    return SUCCESS;
}
int delete_maxheap(float **max_heap, size_t *heap_size, size_t target){
    float *new_max_heap;
    if(target >= (*heap_size) || target < 0)
    {
        #ifdef DEBUG
            fprintf(stderr, "index out of range : delete_maxheap\n");
        #endif
        return OUT_OF_RANGE;
    }
    (*heap_size) = (*heap_size) - 1;
    update_maxheap(max_heap, (*heap_size), target, (*max_heap)[(*heap_size)]);
    new_max_heap = realloc(*max_heap, (*heap_size) * sizeof(float));
    if(new_max_heap == NULL)
    {
        return MEMROY_ALLOCATION_ERROR;
    }
    *max_heap = new_max_heap;
    return SUCCESS;
}
int delete_minheap(float **min_heap, size_t *heap_size, size_t target){
    float *new_min_heap;
    if(target >= (*heap_size) || target < 0)
    {
        #ifdef DEBUG
            fprintf(stderr, "index out of range : delete_minheap\n");
        #endif
        return OUT_OF_RANGE;
    }
    (*heap_size) = (*heap_size) - 1;
    update_minheap(min_heap, (*heap_size), target, (*min_heap)[(*heap_size)]);
    new_min_heap = realloc(*min_heap, (*heap_size) * sizeof(float));
    if(new_min_heap == NULL)
    {
        return MEMROY_ALLOCATION_ERROR;
    }
    *min_heap = new_min_heap;
    return SUCCESS;
}
float extract_max(float **max_heap, size_t *heap_size)
{
    if((*heap_size) < 1)
    {
        return OUT_OF_RANGE;
    }
    float max = (*max_heap)[0];
    (*max_heap)[0] = (*max_heap)[(*heap_size) - 1];
    (*heap_size) = (*heap_size) - 1;
    max_heapify(*max_heap, (*heap_size), 0);
    return max;
}
float extract_min(float **min_heap, size_t *heap_size)
{
    if((*heap_size) < 1)
    {
        return OUT_OF_RANGE;
    }
    float min = (*min_heap)[0];
    (*min_heap)[0] = (*min_heap)[(*heap_size) - 1];
    (*heap_size) = (*heap_size) - 1;
    min_heapify(*min_heap, (*heap_size), 0);
    return min;
}