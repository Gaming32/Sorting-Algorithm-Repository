from sorting import common


def _radixMSD(array, length, min, max, radix, pow):
    if min >= max or pow < 0:
        return
    
    indices = [min] * radix
    for i in range(min, max):
        temp = array[i]
        digit = common.getDigit(temp, pow, radix)
        for j in range(radix - 1, digit, -1):
            array[indices[j]] = array[indices[j - 1]]
            indices[j] = indices[j] + 1
        array[indices[digit]] = temp
        indices[digit] = indices[digit] + 1
    
    for i in range(radix):
        subMin = min if i == 0 else indices[i - 1]
        _radixMSD(array, length, subMin, indices[i], radix, pow - 1)


def _runSort(array, sortLength, bucketCount): 
    highestpower = common.analyzeMaxLog(array, sortLength, bucketCount)
    
    _radixMSD(array, sortLength, 0, sortLength, bucketCount, highestpower)


def sort(seq, base=4):
    _runSort(seq, len(seq), base)
