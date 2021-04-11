#ifndef PDMERGE2_H
#define PDMERGE2_H

#ifndef PDMERGE2_TYPE
    #define PDMERGE2_TYPE int
#endif
#ifndef PDMERGE2_COMPARE
    #define PDMERGE2_COMPARE(a, b) (a - b)
#endif

/*

You must #define PDMERGE2_TYPE and PDMERGE2_COMPARE

*/

/*
MIT License

Copyright (c) 2021 Gaming32

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

#include "utils.h"

#define PDMERGE2_MIN_RUN_SIZE 16


struct pdmerge2_data {
    PDMERGE2_TYPE* copied;
    size_t runCount;
};


void pdmerge2_reverse(PDMERGE2_TYPE* i, PDMERGE2_TYPE* j) {
    PDMERGE2_TYPE tmp;
    while (i < j) {
        tmp = *i;
        *i = *j;
        *j = tmp;
        i++;
        j--;
    }
    
}


void pdmerge2_insertSort(PDMERGE2_TYPE* start, PDMERGE2_TYPE* mid, PDMERGE2_TYPE* end) {
    PDMERGE2_TYPE* pos;
    PDMERGE2_TYPE* pos1;
    PDMERGE2_TYPE cur;
    for (PDMERGE2_TYPE* i = mid; i < end; i++) {
        cur = *i;
        pos = i;
        pos1 = i + 1;
        while (pos >= start && PDMERGE2_COMPARE(*pos, cur) > 0) {
            *pos1 = *pos;
            pos--;
            pos1--;
        }
        *pos1 = cur;
    }
}


void pdmerge2_mergeUp(struct pdmerge2_data *inst, PDMERGE2_TYPE* array, size_t start, size_t mid, size_t end) {
    for (size_t i = 0; i < mid - start; i++) {
        inst->copied[i] = array[i + start];
    }

    size_t bufferPointer = 0;
    size_t left = start;
    size_t right = mid;

    while (left < right && right < end) {
        if (PDMERGE2_COMPARE(inst->copied[bufferPointer], array[right]) <= 0)
            array[left++] = inst->copied[bufferPointer++];
        else
            array[left++] = array[right++];
    }

    while (left < right)
        array[left++] = inst->copied[bufferPointer++];
}


void pdmerge2_mergeDown(struct pdmerge2_data *inst, PDMERGE2_TYPE* array, size_t start, size_t mid, size_t end) {
    for (size_t i = 0; i < end - mid; i++) {
        inst->copied[i] = array[i + mid];
    }

    size_t bufferPointer = end - mid - 1;
    size_t left = mid - 1;
    size_t right = end - 1;

    while (right > left && left >= start) {
        if (PDMERGE2_COMPARE(inst->copied[bufferPointer], array[left]) >= 0)
            array[right--] = inst->copied[bufferPointer--];
        else
            array[right--] = array[left--];
    }

    while (right > left)
        array[right--] = inst->copied[bufferPointer--];
}


void pdmerge2_merge(struct pdmerge2_data *inst, PDMERGE2_TYPE* array, size_t leftStart, size_t rightStart, size_t end) {
    if (end - rightStart < rightStart - leftStart) {
        pdmerge2_mergeDown(inst, array, leftStart, rightStart, end);
    }
    else {
        pdmerge2_mergeUp(inst, array, leftStart, rightStart, end);
    }
}


#define pdmerge2_searchCompare(a, b) PDMERGE2_COMPARE(a, b) <= 0


size_t pdmerge2_identifyRun(struct pdmerge2_data *inst, PDMERGE2_TYPE* array, size_t index, size_t maxIndex) {
    size_t startIndex = index;

    if (index >= maxIndex) {
        return -1;
    }

    bool cmp = pdmerge2_searchCompare(array[index], array[index + 1]);
    index++;

    while (index < maxIndex) {
        bool checkCmp = pdmerge2_searchCompare(array[index], array[index + 1]);
        if (checkCmp != cmp) {
            break;
        }
        index++;
    }

    if (!cmp) {
        pdmerge2_reverse(array + startIndex, array + index);
    }
    size_t length = index - startIndex + 1;
    if (length < PDMERGE2_MIN_RUN_SIZE) {
        size_t end = startIndex + PDMERGE2_MIN_RUN_SIZE;
        if (end > maxIndex + 1)
            end = maxIndex + 1;
        pdmerge2_insertSort(array + startIndex, array + index + 1, array + end);
        return end > maxIndex ? -1 : end;
    }
    if (index >= maxIndex) {
        return -1;
    }
    return index + 1;
}


size_t* pdmerge2_findRuns(struct pdmerge2_data *inst, PDMERGE2_TYPE* array, size_t maxIndex) {
    size_t* runs = (size_t*)malloc((maxIndex / PDMERGE2_MIN_RUN_SIZE + 2) * sizeof(size_t));
    inst->runCount = 0;

    size_t lastRun = 0;
    while (lastRun != -1) {
        runs[inst->runCount++] = lastRun;
        size_t newRun = pdmerge2_identifyRun(inst, array, lastRun, maxIndex);
        lastRun = newRun;
    }

    return runs;
}


void pdmerge2_runSort(struct pdmerge2_data *inst, PDMERGE2_TYPE* array, size_t length) {
    size_t* runs = pdmerge2_findRuns(inst, array, length - 1);
    inst->copied = (PDMERGE2_TYPE*)malloc(length / 2 * sizeof(PDMERGE2_TYPE));

    while (inst->runCount > 1) {
        for (size_t i = 0; i < inst->runCount - 1; i += 2) {
            size_t end = i + 2 >= inst->runCount ? length : runs[i + 2];
            pdmerge2_merge(inst, array, runs[i], runs[i + 1], end);
        }
        for (size_t i = 1, j = 2; i < inst->runCount; i++, j+=2, inst->runCount--) {
            runs[i] = runs[j];
        }
    }

    free(inst->copied);
    free(runs);
}


void pdmerge2(PDMERGE2_TYPE* array, size_t nmemb) {
    struct pdmerge2_data inst;
    pdmerge2_runSort(&inst, array, nmemb);
}

#endif
