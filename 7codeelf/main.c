#include "stdio.h"
#include "sum.c"

int main()
{
    printf("testing");
    int test = sum();
    int* ptr = &test;

    printf("pointer value %p\n", (void*)ptr);
    printf("value at pointer %d\n", *ptr);
    printf("address of the pointer %d\n", **(&ptr));
    return 0;
}