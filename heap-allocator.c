#include <stdio.h>
#include "heap-allocator.h"

// X have to worry about padding or alignment.
// X consider.

// Print the 'dump_mem' in width of 16 bytes.
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
/*
size_t tsize(type t) {
    switch(t) {
        default:
        case SHORT:
            return sizeof(short);
        case CHAR:
            return sizeof(char);
        case FLOAT:
            return sizeof(float);
        case LONG:
            return sizeof(long);
        case STRUCT: // for now.
            return 0;
    }
}

void push(heap *h, void dat) {

}*/

void push(heap* h, const data * dat) {
    size_t size = h->size, pos = h->pos, siz=dat->size;
    //printf("%ld\n", siz);
    if(pos+siz>size) {
        printf("There is not enough memory for the data which you require, you can only use %ld byte(s)\n", size-pos);
        return;
    }
    const char *buffer = dat->address;
    char *write = pos+(char*)(h->addr);
    size_t i;

    for(i=0;i<siz;++i) {
        write[i] = buffer[i] & 0xff;
    }
    pos+=siz;
};

void print(heap* h) {
    dump_mem(h->addr, h->size);
}