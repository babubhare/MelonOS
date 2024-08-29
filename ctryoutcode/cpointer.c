#include "stdio.h"

int main()
{
    int intValue = 100;
    int* intPointer = NULL;
    void* voidPointer = NULL;

    intPointer = &intValue;
    voidPointer = &intPointer;

    printf("Value of Integer: %d \n", intValue);
    printf("Address of Integer: %p \n", &intValue);
    printf("size of pointer address %lu bytes \n", sizeof(&intValue));
    return 0;
}