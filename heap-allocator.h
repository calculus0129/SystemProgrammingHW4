#ifndef HEAP_ALLOC_H
#define HEAP_ALLOC_H

#ifndef size_t
#define size_t unsigned long
#endif

void dump_mem(const void *mem, size_t len);
typedef enum {
    SHORT,
    CHAR,
    FLOAT,
    LONG,
    INT,
    DOUBLE,
    STRUCT,
} type;

size_t tsize(type);

typedef struct {
    void* address;
    size_t size;
    char name[20];
} data;

typedef struct {
    // size: the current bytes of memory allocated.
    size_t size;
    // pos: the current byte position of the end of memory.
    size_t pos;
    // addr: the byte address of the start of the heap.
    void* addr;
    // dsize: the size of the data array darr.
    size_t dsize;
    // darr: the darr.
    data* darr;
} heap;

// print the heap information.
void print(heap* h);

// push a 'data' to the heap.
void push(heap* h, const data *);

// pop a data of heap at a given index.
void pop(heap* h, const size_t idx);

// search the index of a data given its name.
int search(const heap* h, const char * name);

#endif