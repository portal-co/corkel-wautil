#pragma once
#include <stddef.h>
#include <stdint.h>
typedef uint64_t off_t;
extern void *mmap(void *addr, size_t length, int prot, int flags, int fd,
                  off_t offset);
extern int munmap(void *addr, size_t length);
extern void *sbrk(intptr_t increment);
#define MAP_ANONYMOUS 0x1

typedef struct CkMMANHook {
    void * userdata;
    char(*free)(void*,void*);
    void*(*alloc)(void*,void*,size_t,int,int,int,off_t);
    void *(*sbrk)(void*,intptr_t);
} CkMMANHook;
extern CkMMANHook * ck_mmna_hook;