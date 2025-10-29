#pragma once
#include <stdint.h>
#include <stddef.h>
extern void *malloc(size_t size);
extern void free(void *ptr);
extern void *calloc(size_t nmemb, size_t size);
extern void *realloc(void *ptr, size_t size);
extern int posix_memalign(void **memptr, size_t alignment, size_t size);
extern void *aligned_alloc(size_t alignment, size_t bytes);
extern size_t malloc_usable_size(void *ptr);