import sys
import math
import timeit
from collections import Counter
from random import randint


def main():
    a = int(input())
    b = int(input())
    if b - a + 1 >= 9:
        print(9)
    else:
        c = 1
        for i in range(a, b + 1):
            c = c * (i % 9) % 9
        if c == 0:
            print(9)
        else:
            print(c)
        
if __name__ == '__main__':
    start = timeit.default_timer()

    numTest = 1
    while numTest:
        main()
        numTest -= 1

    stop = timeit.default_timer()
    print('Time: ', stop - start, file = sys.stderr)