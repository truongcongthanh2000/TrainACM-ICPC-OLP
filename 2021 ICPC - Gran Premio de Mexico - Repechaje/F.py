import sys
import math
import timeit
from collections import Counter
from random import randint

def main():
    mod = 10**9 + 7
    while True:
        try:
            line = input()
            n = int(line)
            ans = 16 * (n**5) + 11 * (n**3 * (n * n - 1)) // 3
            print(ans % mod)
        except EOFError:
            break

if __name__ == '__main__':
    start = timeit.default_timer()

    numTest = 1
    while numTest:
        main()
        numTest -= 1

    stop = timeit.default_timer()
    print('Time: ', stop - start, file = sys.stderr)
