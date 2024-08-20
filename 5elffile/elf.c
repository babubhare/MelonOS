#include <stdio.h>
#include <stdlib.h>

int stage = 0;

__attribute__((constructor))
void initializer() {
    stage += 1;
    printf("initializer function (stage: %d) \n", stage);
}

__attribute__((destructor))
void finalizer() {
    stage += 1;
    printf("finalizer function (stage: %d) \n", stage);
}

int main(void) {
    stage += 1;
    printf("main function (stage: %d) \n", stage);
    return 0;
}

void alternativeEntryPoint() {
    stage += 1;
    printf("This is an alternative entry point to the program (stage: %d) \n", stage);
    exit(0);
}