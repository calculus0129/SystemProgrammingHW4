#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strcpy()
#include "heap-allocator.h"

int tinput() {
    char tname[10];
    scanf("%s", tname);
    if(!strcmp(tname, "short")) {
        return SHORT;
    }
    if(!strcmp(tname, "char")) {
        return CHAR;
    }
    if(!strcmp(tname, "float")) {
        return FLOAT;
    }
    if(!strcmp(tname, "long")) {
        return LONG;
    }
    if(!strcmp(tname, "struct")) {
        return STRUCT;
    }
    return -1;
}

int main() {
    data xd;
    heap dump={
        .size=64,
        .pos = 0,
        .addr=calloc(64, 1),
    };
    // tn: type number
    int tn;
    void *x=calloc(16, 1);
    xd.address=x;
    char buf[32]="";
    while(1) {
        puts("Do you want to allocate data (1) or deallocate data (2) ?");
        scanf("%s", buf);
        switch(buf[0]) {
            default:
            case '1':
                puts("Input the type of data you want to allocate and the name of the data");
                tn = tinput();
                scanf("%s", xd.name);
                xd.size=tsize(tn);
                puts("Please input a value for the data type");
                switch(tn) {
                    case SHORT:
                        scanf("%hd", (short*)x);
                        break;
                    case CHAR:
                        scanf(" %c", (char*)x);
                        break;
                    case FLOAT:
                        scanf("%f", (float*)x);
                        break;
                    case LONG:
                        scanf("%ld", (long*)x);
                        break;
                    case STRUCT:
                        //scanf("%hd", &x);
                        break;
                    default:
                        break;
                }
                push(&dump, &xd);
                puts("There is memory dump!");
                print(&dump);
                break;
            case '2':
                pop(&dump, 1);
                print(&dump);
                break;
        }
    }
    free(x);

    return 0;
}