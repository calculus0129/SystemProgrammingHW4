#include <stdio.h>
#include <stdlib.h>
#include "heap-allocator.h"

int main() {
    puts("Hello World!");
    short x = 32023;
    char name[20] = "name";
    data xd = {
        .address = &x,
        .size = sizeof x,
        .name = name,
    };
    //dump_mem(&x, sizeof(x));
    double pi = 3.14159296535897932384626433832795;
    //dump_mem(&pi, sizeof(pi));

    // Allocate 64 bytes of memory from heap
    //char *dump = calloc(64, 1);
    // n: the current bytes of memory allocated.
    //size_t n=0;

    //dump_mem(dump, 64);
    heap dump={
        .size=64,
        .pos = 0,
        .addr=calloc(64, 1),
    };
    /*
    // Allocate 64 bytes of memory from heap
    char *dump = calloc(64, 1);
    *(dump+n) = x; n+=2; // 32023 ..?
    *((short*)(dump+n)) = 1231; n+=2; // 1231
    *((short*)(dump+n)) = x; n+=2; // 32023
    */
    push(&dump, &xd);
    print(&dump);

    //dump_mem(dump, 64);
    
    return 0;
}