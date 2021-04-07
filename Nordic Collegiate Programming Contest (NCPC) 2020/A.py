import sys
import math
import timeit
from collections import Counter
from random import randint

def main():
    n = int(input())
    a = list(map(int, input().split()))
    for i in range(n):
        x = list(str(a[i]))
        for j in range(len(x)):
            for c in range(10):
                if j == 0 and c == 0 and len(x) > 1:
                    continue
                tmp = x[j]
                x[j] = chr(c + ord('0'))
                tmp_a = a[i]
                a[i] = 0
                for k in x:
                    a[i] = a[i] * 10 + ord(k) - ord('0')
                if i > 0 and a[i] < a[i - 1]:
                    print(*a)
                    return
                if i < n - 1 and a[i] > a[i + 1]:
                    print(*a)
                    return
                a[i] = tmp_a
                x[j] = tmp
    print("impossible")
if __name__ == '__main__':
    start = timeit.default_timer()

    numTest = 1
    # numTest = int(input())
    while numTest > 0:
        main()
        numTest -= 1

    stop = timeit.default_timer()
    print('Time: ', stop - start, file = sys.stderr)