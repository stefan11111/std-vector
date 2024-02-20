#ifndef __LIST_H_INCLUDED__
#define __LIST_H_INCLUDED__

#include <stdlib.h>
#include <string.h>

typedef struct{
    char *elements;
    void (*constructor)(void *elem);
    void (*destructor)(void *elem);
    void* (*copy)(void * restrict dest, const void * restrict src, size_t size);
    void* (*move)(void * restrict dest, const void * restrict src, size_t size);
    void (*malloc_error) ();
    size_t size;
    size_t total_size;
} vec_t;

void init_vector(vec_t *ptr, size_t size, size_t num_elements, void (*_init_vector)(vec_t *ptr));
void resize_vector(vec_t *ptr, size_t num_elements);
void free_vector(vec_t *ptr);
void write_element(vec_t *ptr, size_t pos, void *data, size_t size);
void read_element(vec_t *ptr, size_t pos, void *data, size_t size);

#endif