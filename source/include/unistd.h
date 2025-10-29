/* Stub include file to support dlmalloc. */

#include <stdint.h>
// #include <ekern/PAGESIZE.h>

#define sysconf(name) 0x10000
#define _SC_PAGESIZE

/* Declare sbrk. */
void *sbrk(intptr_t increment) __attribute__((__warn_unused_result__));
