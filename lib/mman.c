#include "alloc.h"
#include "sys/mman.h"
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset){
    if(flags & MAP_ANONYMOUS){
        return malloc(length);
    }
}
int munmap(void *addr, size_t length){
    free(addr);
    return 0;
}