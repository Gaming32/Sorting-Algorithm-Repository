#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <float.h>

#define XSTR(s) STR(s)
#define STR(s)  #s

#include "double_insertion.h"
#define SORT_TYPE DOUBLE_INSERTION_TYPE
#define SORT_FUNC double_insertion

#define LENGTH 131072
#define SEED   time(NULL)
#define REPS   10


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


double timeSort(SORT_TYPE* array) {
    srand(SEED);
    for (int i = 0; i < LENGTH; i++) {
        array[i] = randrange(LENGTH);
    }
    long startTime = clock();
    SORT_FUNC(array, LENGTH);
    double total = (double)(clock() - startTime) / CLOCKS_PER_SEC;
    return total;
}


int main() {
    SORT_TYPE* array = (int*)malloc(LENGTH * sizeof(SORT_TYPE));
    double total = 0;
    double minimum = DBL_MAX;
    printf("Running sort %s %i times on %i numbers...\n", XSTR(SORT_FUNC), REPS, LENGTH);
    for (int i = 0; i < REPS; i++) {
        double time = timeSort(array);
        total += time;
        if (time < minimum) {
            minimum = time;
        }
        printf("Ran sort %i/%i times (took %f seconds)\r", i + 1, REPS, time);
    }
    printf("Ran sort %s %i times (total %f seconds):\n", XSTR(SORT_FUNC), REPS, total);
    printf("  - Average time: %f seconds\n", total / REPS);
    printf("  - Minimum time: %f seconds\n", minimum);
    // printf("Time took: %f seconds\n", time);
}
