#ifndef DOUBLE_INSERTION_H
#define DOUBLE_INSERTION_H

#ifndef DOUBLE_INSERTION_TYPE
    #define DOUBLE_INSERTION_TYPE int
#endif
#ifndef DOUBLE_INSERTION_COMPARE
    #define DOUBLE_INSERTION_COMPARE(a, b) (a - b)
#endif

/*

You must #define DOUBLE_INSERTION_TYPE and DOUBLE_INSERTION_COMPARE

*/

/*
MIT License

Copyright (c) 2020-2021 Gaming32 and Morwenn

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


void insertionSort(DOUBLE_INSERTION_TYPE* start, DOUBLE_INSERTION_TYPE* end) {
    DOUBLE_INSERTION_TYPE *left  = start + (end - start) / 2 - 1;
    DOUBLE_INSERTION_TYPE *right = left + 1;
    if (DOUBLE_INSERTION_COMPARE(*left, *right) > 0) {
        DOUBLE_INSERTION_TYPE tmp;
        swap(left, right, tmp);
    }
    left--;
    right++;

    DOUBLE_INSERTION_TYPE leftItem, rightItem, *pos, *pos1;
    while (left >= start && right < end)
    {
        if (DOUBLE_INSERTION_COMPARE(*left, *right) > 0) {
            leftItem  = *right;
            rightItem = *left;

            pos  =  left + 1;
            pos1 =  left;
            while (pos <= right && DOUBLE_INSERTION_COMPARE(*pos, leftItem) <= 0) {
                *pos1++ = *pos++;
            }
            *pos1 = leftItem;

            pos  =  right - 1;
            pos1 =  right;
            while (pos >= left && DOUBLE_INSERTION_COMPARE(*pos, rightItem) >= 0) {
                *pos1-- = *pos--;
            }
            *pos1 = rightItem;
        }
        else {
            leftItem  = *left;
            rightItem = *right;

            pos  =  left + 1;
            pos1 =  left;
            while (DOUBLE_INSERTION_COMPARE(*pos, leftItem) < 0) {
                *pos1++ = *pos++;
            }
            *pos1 = leftItem;

            pos  =  right - 1;
            pos1 =  right;
            while (DOUBLE_INSERTION_COMPARE(*pos, rightItem) > 0) {
                *pos1-- = *pos--;
            }
            *pos1 = rightItem;
        }

        left--;
        right++;
    }

    if (right < end) {
        rightItem  = *right;
        pos        =  right - 1;
        pos1       =  right;
        while (DOUBLE_INSERTION_COMPARE(*pos, rightItem) > 0) {
            *pos1-- = *pos--;
        }
        *pos1 = rightItem;
    }
}

void double_insertion(DOUBLE_INSERTION_TYPE* array, size_t nmemb) {
    insertionSort(array, array + nmemb);
}

#endif
