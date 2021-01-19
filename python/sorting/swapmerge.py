"""SwapMergeSort is an in-place variant of Binary Merge Sort.
Module containing `sort` function"""


def _binaryInsertSort(array, start=0, end=None):
    if end is None:
        end = len(array)
    for i in range(start, end):
        num = array[i]
        lo = start
        hi = i
        
        while lo < hi:
            mid = lo + ((hi - lo) // 2)
            
            if num < array[mid]: # do NOT move equal elements to right of inserted element this maintains stability!
                hi = mid
            else:
                lo = mid + 1
        
        # item has to go into position lo

        j = i - 1
        
        while j >= lo:
            array[j + 1] = array[j]
            j -= 1
        array[lo] = num


def _moveDown(array, start, dest):
    for i in range(dest, start):
        array[i], array[start] = array[start], array[i]


def _merge(array, leftStart, rightStart, end):
    left = leftStart
    right = rightStart

    while left < right:
        if left >= end or right >= end:
            break
        elif array[left] <= array[right]:
            left += 1
        else:
            _moveDown(array, right, left)
            left += 1
            right += 1


def _mergeRun(array, start, mid, end, length):
    if start == mid:
        return

    _mergeRun(array, start, (mid+start)//2, mid, length)
    _mergeRun(array, mid, (mid+end)//2, end, length)

    if end - start < 32 :
        return
    elif end - start == 32 :
        _binaryInsertSort(array, start, min(length, end + 1))
    else:
        _merge(array, start, mid, end)


def sort(array):
    "Sort array using SwapMergeSort"
    length = len(array)

    if length < 32 :
        _binaryInsertSort(array, 0, length)
        return

    start = 0
    end = length
    mid = start + ((end - start) // 2)
    
    _mergeRun(array, start, mid, end, length)


if __name__ == '__main__':
    l = list(range(256))
    # print(l)
    import random
    random.shuffle(l)
    # print(l)
    import cProfile
    cProfile.run('sort(l)')
    # swapmergesort(l)
    # print(l)
