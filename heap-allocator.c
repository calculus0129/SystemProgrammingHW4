#include <stdio.h>
#include <stdlib.h> // for explicit calloc and free()
#include <string.h> // for strcpy()
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

void push(heap* h, const data * dat) {
    size_t size = h->size, pos = h->pos, siz=dat->size, dsize=h->dsize;
    //printf("%ld\n", siz);
    
    // Checking Safety for allocation
    if(pos+siz>size) {
        printf("There is not enough memory for the data which you require, you can only use %ld byte(s)\n", size-pos);
        return;
    }
    // Extend The dynamic array darr of *h:
    // 1. move all the data to dar with dynamic memories.
    // 2. move address of dar to h->darr.
    data* dar = calloc(dsize+1, sizeof(data));
    size_t i;
    for(i=0;i<dsize;++i) {
        dar[i] = h->darr[i];
    }
    free(h->darr);
    // Determine fields of the last element of darr.
    char *write = dar[dsize].address = pos+(char*)(h->addr);
    dar[dsize].size = siz;
    strcpy(dar[dsize].name,dat->name);
    
    // Now, write the bytes of dat on the heap h.
    const char *buffer = dat->address;
    for(i=0;i<siz;++i) {
        write[i] = buffer[i] & 0xff;
    }

    // Modify the byte position of h.
    h->pos+=siz;
    // Give address of dar to h->darr.
    h->darr = dar;
    // Increase the dsize too.
    h->dsize++;
};

void print(heap* h) {
    dump_mem(h->addr, h->size);
    puts("------Data you have now------");
    for(size_t i=0,e=h->dsize;i<e;++i) {
        puts(h->darr[i].name);
        //printf("") // Print additional info of data.
    }
}

void pop(heap* h, const size_t idx) {
    // pop the data out of darr first.
    size_t i, e;
    // pd: popped data
    data pd = h->darr[idx];
    size_t size = pd.size;
    for(i=idx,e=h->dsize-1;i<e;++i) {
        h->darr[i]=h->darr[i+1];
        h->darr[i].address = (char*)h->darr[i].address - size;
    }
    // pop in the memory.
    for(i=(char*)pd.address-(char*)h->addr,e=h->pos-size;i<e;++i) {
        ((char*)h->addr)[i] = ((char*)h->addr)[i+size];
    }
    for(i=e,e=h->pos;i<e;++i) {
        ((char*)h->addr)[i] = '\0';
    }
    // Change attributes of h.
    h->pos -= size;
    h->dsize--;
}

int search(const heap* h, const char * name) {
    int i=0,e=h->dsize;
    for(;i<e;++i) {
        if(!strcmp(h->darr[i].name, name)) return i;
    }
    return -1;
}
