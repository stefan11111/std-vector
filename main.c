#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

volatile char out;
volatile char* p_out = &out;

static inline void nop()
{
}

static inline void _init_vector(vec_t *ptr)
{
    ptr->constructor = &nop;

    ptr->destructor = &nop;

    ptr->copy = &memcpy;

    ptr->move = &memcpy;

    ptr->malloc_error = &exit;
}

int main()
{
    size_t size = 8;
    size_t n = 10;
    vec_t vec;

    char *str="very long string, longer that 8 char's";

    char dest[100];

    char *p = dest;

    init_vector(&vec, size, n, &_init_vector);
    for(size_t i = 0; i < n; i++) {
        write_element(&vec, i, str, size);
    }

    n = 5;

    resize_vector(&vec, n);

    for(size_t i = 0; i < n; i++) {
        write_element(&vec, i, str, size);
    }

    for(size_t i = 0; i < n; i++) {
        read_element(&vec, i, p, size);
        printf("%s\n", p);
    }

    return 0;
}

