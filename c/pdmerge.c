/*

You must #define PDMERGE_TYPE and PDMERGE_COMPARE

*/

/*
MIT License

Copyright (c) 2020 Gaming32

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#include "pdmerge.h"
#include "utils.h"

#define IS_FIRST_RUN 0b01
#define IS_LAST_RUN  0b10


struct pdmerge_data
{
    int smallestRunSize;
    int copiedLength;
    PDMERGE_TYPE* copied;
};


struct runlist
{
    int index;
    struct runlist* next;
    struct runlist* prev;
    uint8_t firstLast;
    int runCount;
};

struct runlist* runlist_new(int index) {
    struct runlist result;
    result.index = index;
    result.next = &result;
    result.prev = &result;
    result.firstLast = IS_FIRST_RUN | IS_LAST_RUN;
    result.runCount = 1;
}

void runlist_addEnd(struct runlist* runs, int index) {
    struct runlist new;
    new.index = index;

    struct runlist* lastRun = runs->prev;
    lastRun->next = &new;
    runs->prev = &new;
    lastRun->firstLast ^= IS_LAST_RUN;
    new.firstLast |= IS_LAST_RUN;

    runs->runCount++;
}

void runlist_remove(struct runlist* first, struct runlist* elem) {
    elem->prev->next = elem->next->prev;
    elem->next->prev = elem->prev->next;
    if (elem->firstLast & IS_FIRST_RUN) {
        elem->next->firstLast |= IS_FIRST_RUN;
    }
    else if (elem->firstLast & IS_LAST_RUN) {
        elem->prev->firstLast |= IS_LAST_RUN;
    }

    first->runCount--;
}


void ensureCapacity(struct pdmerge_data *inst, int length) {
    if (length > inst->copiedLength) {
        inst->copied = realloc(inst->copied, length * sizeof(PDMERGE_TYPE));
        inst->copiedLength = length;
    }
}


void mergeDown(struct pdmerge_data *inst, PDMERGE_TYPE* array, int start, int mid, int end) {
    ensureCapacity(inst, end - mid);
    for (int i = 0; i < end - mid; i++) {
        inst->copied[i] = array[i + mid];
    }

    int bufferPointer = end - mid - 1;
    int left = mid - 1;
    int right = end - 1;

    while (right > left && left >= start)
    {
        if (PDMERGE_COMPARE(inst->copied[bufferPointer], array[right]) <= 0)
            array[right--] = inst->copied[bufferPointer--];
        else
            array[right--] = array[left--];
    }

    while (right > left)
        array[right--] = inst->copied[bufferPointer--];
}


void merge(struct pdmerge_data *inst, PDMERGE_TYPE* array, int leftStart, int rightStart, int end) {
    // if (end - rightStart < rightStart - leftStart) {
        mergeDown(inst, array, leftStart, rightStart, end);
    // }
    // else {

    // }
}


#define compare(a, b) PDMERGE_COMPARE(a, b) <= 0

#define EMPTY_RUNLIST IS_FIRST_RUN | IS_LAST_RUN


int identifyRun(struct pdmerge_data *inst, PDMERGE_TYPE* array, int index, int maxIndex) {
    int startIndex = index;

    if (index >= maxIndex) {
        return -1;
    }

    bool cmp = compare(array[index], array[index + 1]);
    index++;

    while (index < maxIndex) {
        printf("index: %i\n", index);
        bool checkCmp = compare(array[index], array[index + 1]);
        if (checkCmp != cmp) {
            break;
        }
        index++;
    }
    printf("run: %i-%i\n", startIndex, index);

    if (!cmp) {
        reverse(array, startIndex, index);
    }
    if (index >= maxIndex) {
        return -1;
    }
    return index + 1;
}


struct runlist* findRuns(struct pdmerge_data *inst, PDMERGE_TYPE* array, int maxIndex) {
    struct runlist* runs = runlist_new(0);

    int lastRun = 0;
    while (lastRun != -1) {
        printf("runcount: %i\n", runs->runCount);
        int newRun = identifyRun(inst, array, lastRun, maxIndex);
        return runs;
        if (newRun == -1) {
            inst->smallestRunSize = min(inst->smallestRunSize, maxIndex - lastRun + 1);
            break;
        }
        inst->smallestRunSize = min(inst->smallestRunSize, newRun - lastRun + 1);
        lastRun = newRun;
        runlist_addEnd(runs, lastRun);
    }

    return runs;
}


void runSort(struct pdmerge_data *inst, PDMERGE_TYPE* array, int length) {
    inst->smallestRunSize = INT_MAX;
    struct runlist *runs = findRuns(inst, array, length - 1);
    goto bye;
    inst->copiedLength = inst->smallestRunSize;
    inst->copied = malloc(inst->smallestRunSize * sizeof(PDMERGE_TYPE));

    while (runs->firstLast != EMPTY_RUNLIST)
    {
        struct runlist* currun = runs;
        for (int i = 0; i < runs->runCount - 1; i += 2) {
            struct runlist* mid = currun->next;
            int end = i + 2 >= runs->runCount ? length : mid->next->index;
            merge(inst, array, currun->index, mid->index, end);
            currun = mid->next;
        }
        currun = runs->next;
        for (int i = 1; i < runs->runCount; i++) {
            runlist_remove(runs, currun);
            currun = currun->next->next;
        }
    }

    bye:
    free(inst->copied);
}


void pdmerge(PDMERGE_TYPE* array, int nmemb) {
    struct pdmerge_data inst;
    runSort(&inst, array, nmemb);
}
