from sorting import common


class PDMerge:
    smallestRunSize: int
    copied: list

    def ensureCapacity(self, length):
        if length > len(self.copied):
            self.copied = [0] * length

    def mergeUp(self, array, start, mid, end):
        self.ensureCapacity(mid - start)
        for i in range(mid - start):
            self.copied[i] = array[i + start]

        bufferPointer = 0
        left = start
        right = mid

        while left < right and right < end:
            if self.copied[bufferPointer] <= array[right]:
                array[left] = self.copied[bufferPointer]
                left += 1
                bufferPointer += 1
            else:
                array[left] = array[right]
                left += 1
                right += 1
        
        while left < right:
            array[left] = self.copied[bufferPointer]
            left += 1
            bufferPointer += 1

    def mergeDown(self, array, start, mid, end):
        self.ensureCapacity(end - mid)
        for i in range(end - mid):
            self.copied[i] = array[i + mid]

        bufferPointer = end - mid - 1
        left = mid - 1
        right = end - 1

        while right > left and left >= start:
            if self.copied[bufferPointer] > array[left]:
                array[right] = self.copied[bufferPointer]
                right -= 1
                bufferPointer -= 1
            else:
                array[right] = array[left]
                right -= 1
                left -= 1
        
        while right > left:
            array[right] = self.copied[bufferPointer]
            right -= 1
            bufferPointer -= 1

    def merge(self, array, leftStart, rightStart, end):
        if end - rightStart < rightStart - leftStart:
            self.mergeDown(array, leftStart, rightStart, end)
        else:
            self.mergeUp(array, leftStart, rightStart, end)

    def compare(self, a, b):
        return a <= b

    def identifyRun(self, array, index, maxIndex):
        startIndex = index

        if index >= maxIndex:
            return -1

        cmp = self.compare(array[index], array[index + 1])
        index += 1

        while index < maxIndex:
            checkCmp = self.compare(array[index], array[index + 1])
            if checkCmp != cmp:
                break
            index += 1
        
        if not cmp:
            common.reverse(array, startIndex, index)
        if index >= maxIndex:
            return -1
        return index + 1

    def findRuns(self, array, maxIndex):
        runs = []

        lastRun = 0
        while lastRun != -1:
            runs.append(lastRun)
            newRun = self.identifyRun(array, lastRun, maxIndex)
            if newRun == -1:
                self.smallestRunSize = min(self.smallestRunSize, maxIndex - lastRun + 1)
            else:
                runSize = newRun - lastRun + 1
                self.smallestRunSize = min(self.smallestRunSize, runSize)
            lastRun = newRun
        
        return runs

    def runSort(self, array, length):
        self.smallestRunSize = 0
        runs = self.findRuns(array, length - 1)
        self.copied = [0] * self.smallestRunSize

        while len(runs) > 1:
            for i in range(0, len(runs) - 1, 2):
                end = length if i + 2 >= len(runs) else runs[i + 2]
                self.merge(array, runs[i], runs[i + 1], end)
            i = 1
            while i < len(runs):
                del runs[i]
                i += 1


def sort(seq):
    inst = PDMerge()
    inst.runSort(seq, len(seq))


if __name__ == '__main__':
    import random
    length = 32
    arr = [random.randrange(length) for _ in range(length)]
    print(arr)
    sort(arr)
    print(arr)
