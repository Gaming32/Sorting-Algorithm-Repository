#define min(a, b) (((a) < (b)) ? (a) : (b))


#define swap(array, a, b) { \
    PDMERGE_TYPE tmp = array[a]; \
    array[a] = array[b]; \
    array[b] = tmp; \
}


#define reverse(array, start, end) { \
    for (int i = start, j = end; i < j; i++, j--) { \
        swap(array, i, j); \
    } \
}
