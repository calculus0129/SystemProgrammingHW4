#include <stdio.h>
#include "heap-allocator.h"

// X have to worry about padding or alignment.

void dump_mem(const void *mem, size_t len) {
    const char *buffer = mem;
    size_t i;
    for(i=0;i<len;++i) {
        if(i>0 && i%16 == 0) {
            printf("\n");
        }
        printf("%02x ", buffer[i] & 0xff);
    }
    puts("");
}