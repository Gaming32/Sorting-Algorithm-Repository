import math


def swap(array, i, j):
    array[i], array[j] = array[j], array[i]


def analyzeMaxLog(array, length, base): 
    max = 0
    nat_base_log = math.log1p(base)
    
    for i in range(length):
        log = int(math.log1p(array[i]) / nat_base_log)
        
        if log > max:
            max = log
    
    return max


def getDigit(a, power, radix):
    digit = int(a / pow(radix, power)) % radix
    return digit


def reverse(array, start, length):
    i = start
    while i < start + ((length - start + 1) // 2):
        swap(array, i, start + length - i)
        i += 1
