import sys
sys.path.insert(1, '.')
sys.path.append('c')
sys.path.append('..')

from pysorting import pdmerge, pdmerge2, double_insertion
import stable_checker


for func in (pdmerge, pdmerge2, double_insertion):
    result = stable_checker.simple_sort(func)
    stable = stable_checker.IntegerWrapper.sequence_out_of_place(result)
    if stable == -1:
        print(func.__name__, 'is stable')
    else:
        print(func.__name__, 'is not stable (indices', stable, 'and', stable + 1, 'are out of order)')
    print('   ', result[:10], '...')
