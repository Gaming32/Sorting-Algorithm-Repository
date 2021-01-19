#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "pdmerge.h"

#define LENGTH 32


PDMERGE_TYPE randrange(PDMERGE_TYPE high) {
    return (PDMERGE_TYPE)(rand() * high / RAND_MAX);
}


void printArray(PDMERGE_TYPE* array, int length) {
    printf("[%i", array[0]);
    for (int i = 1; i < length; i++) {
        printf(", %i", array[i]);
    }
    printf("]\n");
}


int main() {
    PDMERGE_TYPE* array = (int*)malloc(LENGTH * sizeof(PDMERGE_TYPE));
    srand(time(NULL));
    for (int i = 0; i < LENGTH; i++) {
        array[i] = randrange(LENGTH);
    }
    printArray(array, LENGTH);
    pdmerge(array, LENGTH);
    printArray(array, LENGTH);
}
