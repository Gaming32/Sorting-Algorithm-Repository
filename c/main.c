#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "double_insertion.h"
#define SORT_TYPE DOUBLE_INSERTION_TYPE
#define SORT_FUNC double_insertion

#define LENGTH 512
#define SEED   time(NULL)


SORT_TYPE randrange(SORT_TYPE high) {
    return (SORT_TYPE)(rand() * high / RAND_MAX);
}


void printArray(SORT_TYPE* array, int length) {
    printf("[%i", array[0]);
    for (int i = 1; i < length; i++) {
        printf(", %i", array[i]);
    }
    printf("]\n");
}


int main() {
    SORT_TYPE* array = (int*)malloc(LENGTH * sizeof(SORT_TYPE));
    srand(SEED);
    for (int i = 0; i < LENGTH; i++) {
        array[i] = randrange(LENGTH);
    }
    // printArray(array, LENGTH);
    long startTime = clock();
    SORT_FUNC(array, LENGTH);
    printf("Time took: %f seconds\n", (double)(clock() - startTime) / CLOCKS_PER_SEC);
    // printArray(array, LENGTH);
}
