#ifndef HEAP_ALLOC_H
#define HEAP_ALLOC_H

// Maximum number of bytes of allocation.
#define MAX_ALLOC 64

#ifndef size_t
#define size_t unsigned long
#endif

void dump_mem(const void *mem, size_t len);
typedef enum {
    SHORT,
    CHAR,
    FLOAT,
    LONG,
    STRUCT,
} type;

size_t tsize(type);

typedef struct {
    void* address;
    size_t size;
    char name[20];
} data;

typedef struct {
    size_t size;
    size_t pos;
    void* addr;
} heap;

void print(heap* h);
void push(heap* h, const data *);

//data push(const void *dump, size_t len, )

#endif