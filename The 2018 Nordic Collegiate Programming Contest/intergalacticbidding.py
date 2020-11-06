import sys
import math
import timeit
from collections import Counter
from random import randint


def main():
    n, s = map(int, input().split())
    a = []
    for i in range(n):
        x, y = map(str, input().split())
        a.append([x, int(y)])
    a.sort(key = lambda x: x[1], reverse=True)
    res = []
    for i in range(n):
        if a[i][1] <= s and a[i][1] * 2 >= s:
            res.append(a[i][0])
            s -= a[i][1]
    if s == 0:
        print(len(res))
        for x in res:
            print(x)
    else:
        print(0)
        
if __name__ == '__main__':
    start = timeit.default_timer()

    numTest = 1
    # numTest = int(input())
    while numTest > 0:
        main()
        numTest -= 1

    stop = timeit.default_timer()
    print('Time: ', stop - start, file = sys.stderr)