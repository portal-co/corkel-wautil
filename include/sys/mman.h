#pragma once
#include <stddef.h>
#include <stdint.h>
typedef uint64_t off_t;
extern void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
extern int munmap(void *addr, size_t length);
extern void *sbrk(intptr_t increment);
#define MAP_ANONYMOUS 0x1