#define min(a, b) (((a) < (b)) ? (a) : (b))


#define swap(array, a, b) { \
    PDMERGE_TYPE tmp = array[a]; \
    array[a] = array[b]; \
    array[b] = tmp; \
}


#define reverse(array, start, length) { \
    for (int i = start; i < start + ((length - start + 1) / 2); i++) { \
        swap(array, i, start + length - i); \
    } \
}
