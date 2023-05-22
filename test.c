#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strcpy()
#include "heap-allocator.h"

int tinput(char tname[10]) {
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
    if(!strcmp(tname, "int")) {
        return INT;
    }
    if(!strcmp(tname, "double")) {
        return DOUBLE;
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
    // tn: type number, dn: data number
    int tn, dn, i, n, r=1, struct_type_error=0;
    void *x=calloc(64<<3, 1);
    void *xin = x;
    xd.address=x;
    char buf[32]="", tname[10];
    while(r) {
        puts("Do you want to allocate data (1) or deallocate data (2) ?");
        scanf("%s", buf);
        switch(buf[0]) {
            case '1':
                puts("Input the type of data you want to allocate and the name of the data");
                scanf("%s", tname);
                tn = tinput(tname);
                scanf("%s", xd.name);
                xd.size=tsize(tn);
                // Checking Invalid type name
                if(tn==-1) {
                    printf("Please input a valid type name!\n");
                    printf("e.g. int, short, char, float, long, double, struct\n\n");
                    break;
                }
                switch(tn) {
                    case SHORT:
                        puts("Please input a value for the data type");
                        scanf("%hd", (short*)x);
                        break;
                    case CHAR:
                        puts("Please input a value for the data type");
                        scanf(" %c", (char*)x);
                        break;
                    case FLOAT:
                        puts("Please input a value for the data type");
                        scanf("%f", (float*)x);
                        break;
                    case LONG:
                        puts("Please input a value for the data type");
                        scanf("%ld", (long*)x);
                        break;
                    case INT:
                        puts("Please input a value for the data type");
                        scanf("%d", (int*)x);
                        break;
                    case DOUBLE:
                        puts("Please input a value for the data type");
                        scanf("%lf", (double*)x);
                        break;
                    case STRUCT:
                        puts("How many data should be in the struct");
                        scanf("%d", &n);
                        if(n>64) {
                            puts("TOO many data for 64 bytes");
                            xd.size=0;
                        }
                        puts("Please input each type and its value");
                        xin=x;
                        for(i=0;i<n;++i) {
                            scanf("%s", tname);
                            tn = tinput(tname);
                            do {
                                struct_type_error=0;
                                switch(tn) {
                                    case SHORT:
                                        scanf("%hd", (short*)xin);
                                        break;
                                    case CHAR:
                                        scanf(" %c", (char*)xin);
                                        break;
                                    case FLOAT:
                                        scanf("%f", (float*)xin);
                                        break;
                                    case LONG:
                                        scanf("%ld", (long*)xin);
                                        break;
                                    case INT:
                                        scanf("%d", (int*)xin);
                                        break;
                                    case DOUBLE:
                                        scanf("%lf", (double*)xin);
                                        break;
                                    case -1:
                                        struct_type_error=1;
                                        printf("Please input a valid type name!\n");
                                        printf("e.g. int, short, char, float, long, double, struct\n\n");
                                        break;
                                }
                            } while(struct_type_error);
                            xin = (char*)xin + tsize(tn);
                            xd.size+=tsize(tn);
                        }
                        break;
                    //default: // Cannot happen
                    //    break;
                }
                push(&dump, &xd);
                print(&dump);
                break;
            case '2':
                puts("Input the name of data you want to deallocate");
                scanf("%s", buf);
                dn = search(&dump, buf);
                if(dn>=0) {
                    pop(&dump, dn);
                    printf("%s has been deallocated\n", buf);
                    print(&dump);
                }
                else {
                    printf("ValueError: Cannot find the name in data list\n");
                }
                break;
            default:
                r=0;
                puts("Good Bye!");
                break;
        }
    }
    free(x);

    return 0;
}