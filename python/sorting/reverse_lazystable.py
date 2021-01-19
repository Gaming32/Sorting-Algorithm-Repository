from sorting.common import swap
from math import inf


def _moveDown(array, start, dest, size):
    amount = start - dest
    if size > 1:
        while amount >= size:
            i = start
            while i > start - size:
                swap(array, i - 1, i + size - 1)
                i -= 1
            start -= size
            amount -= size
        if amount > 0:
            _moveDown(array, start, dest, size // 2)
            _moveDown(array, start + size // 2, dest + size // 2, size - (size // 2))
    else:
        tmp = array[start]
        for i in range(start, dest, -1):
            array[i] = array[i - 1]
        array[dest] = tmp


def _merge(array, start, mid, end):
    lastValue = -inf

    while start < mid:
        size = 0
        for i in range(mid, end):
            if array[i] < array[start] and array[i] >= lastValue:
                size += 1
            else:
                break
        if size > 0:
            _moveDown(array, mid, start, size)

        start += size + 1
        mid += size
        lastValue = array[start - 1]


def _runSort(array, length):
    gap = 2
    while gap <= length:
        for i in range(0, length, gap):
            _merge(array, i, i + gap // 2, i + gap)
        gap *= 2

    if length - gap // 2 > 0:
        _merge(array, 0, gap // 2, length)


def sort(seq):
    _runSort(seq, len(seq))
