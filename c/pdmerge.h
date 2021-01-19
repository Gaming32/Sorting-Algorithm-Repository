#ifndef PDMERGE_H
#define PDMERGE_H

#ifndef PDMERGE_TYPE
    #define PDMERGE_TYPE int
#endif
#ifndef PDMERGE_COMPARE
    #define PDMERGE_COMPARE(a, b) (b - a)
#endif

void pdmerge(PDMERGE_TYPE* array, int nmemb);

#endif