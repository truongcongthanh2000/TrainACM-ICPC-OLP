import sys
import math
import timeit
from collections import Counter
from random import randint


def main():
    n = int(input())
    if n == 0:
        print(2)
        return
    q = [0, 9]
    res = 9
    for i in range(2, n + 1):
        value = 9 * 10**((i - 1) // 2) + q[i - 1]
        q.append(value)
        res += value
    print(res + 2)
        
if __name__ == '__main__':
    start = timeit.default_timer()

    #numTest = 1
    numTest = int(input())
    while numTest > 0:
        main()
        numTest -= 1

    stop = timeit.default_timer()
    print('Time: ', stop - start, file = sys.stderr)