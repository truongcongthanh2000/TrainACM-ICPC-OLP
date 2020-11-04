import sys

t = int(input())
while t > 0:
    t -= 1
    n = int(input())
    while n % 7 != 0:
        rv_n = int(str(n)[::-1])
        n += rv_n
    print(n)    
        

