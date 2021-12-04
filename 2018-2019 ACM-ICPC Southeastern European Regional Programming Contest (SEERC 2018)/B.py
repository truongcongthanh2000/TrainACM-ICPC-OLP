import sys
import math
import timeit
from collections import Counter
from random import randint
from math import comb

def main():
    a, b, c, n = map(int, input().split())
    l = len(set([a, b, c]))
    if l == 3:
        x = 6
    elif l == 2:
        x = 3
    else:
        x = 1
    MOD = 2**64
    print((comb(n, 3) - n * comb((n - 1) // 2, 2)) * x % MOD)

if __name__ == '__main__':
    start = timeit.default_timer()

    numTest = 1
    while numTest:
        main()
        numTest -= 1

    stop = timeit.default_timer()
    print('Time: ', stop - start, file = sys.stderr)
