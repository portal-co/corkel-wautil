#include "sys/mman.h"
#include "alloc.h"
#include "errno.h"
#include "sys/pagesize.h"
#include <stdint.h>
#include <sys/mman.h>
CkMMANHook *ck_mman_hook;
void *mmap(void *addr, size_t length, int prot, int flags, int fd,
           off_t offset) {
  if (flags & MAP_ANONYMOUS) {
    if ((length << PAGESIZE_LOG2) >> PAGESIZE_LOG2 != length)
      if (ck_mman_hook)
        return ck_mman_hook->alloc(ck_mman_hook->userdata, addr, length, prot,
                                   flags, fd, offset);
#ifdef __wasm__
    return malloc(length);
#endif
  }
  if (ck_mman_hook)
    return ck_mman_hook->alloc(ck_mman_hook->userdata, addr, length, prot,
                               flags, fd, offset);
}
int munmap(void *addr, size_t length) {
  if (ck_mman_hook && ck_mman_hook->free(ck_mman_hook->userdata, addr))
    return 0;
#ifdef __wasm__
  free(addr);
#endif
  return 0;
}
static int did_mem_brk = 0;
void *sbrk(intptr_t increment) {
  if (!did_mem_brk &&
      (increment << PAGESIZE_LOG2) >> PAGESIZE_LOG2 == increment) {
#ifdef __wasm__
    // sbrk(0) returns the current memory size.
    if (increment == 0) {
      // The wasm spec doesn't guarantee that memory.grow of 0 always succeeds.
      return (void *)(__builtin_wasm_memory_size(0) * PAGESIZE);
    }

    // We only support page-size increments.
    if (increment % PAGESIZE != 0) {
      // abort();
    }

    // WebAssembly doesn't support shrinking linear memory.
    if (increment < 0) {
      // abort();
    }

    uintptr_t old =
        __builtin_wasm_memory_grow(0, (uintptr_t)increment / PAGESIZE);

    if (old == SIZE_MAX) {
      errno = ENOMEM;
      return (void *)-1;
    }

    return (void *)(old * PAGESIZE);
#endif
  }
  if (ck_mman_hook) {
    did_mem_brk = 1;
    return ck_mman_hook->sbrk(ck_mman_hook->userdata, increment);
  }
}
