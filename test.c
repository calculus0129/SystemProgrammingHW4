#include <stdio.h>
#include "heap-allocator.h"

int main() {
    puts("Hello World!");
    int x = 5;
    dump_mem(&x, sizeof(x));
    double pi = 3.14159296535897932384626433832795;
    dump_mem(&pi, sizeof(pi));

    return 0;
}