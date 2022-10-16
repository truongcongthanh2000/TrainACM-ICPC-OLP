import sys

def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)

def norm(a, b):
    c = gcd(a, b)
    return a // c, b // c

def solve(p, q):
    op = []

    while p != q:
        p, q = norm(p, q)
        if p < q:
            if q % p == 0:
                op.append([q // p - 1, 1])
                break
            op.append([q // p, 1])
            q = q % p
        else:
            if p % q == 0:
                op.append([p // q - 1, 0])
                break
            op.append([p // q, 0])
            p = p % q
    
    op = op[::-1]

    ans = 0
    for idx in range(len(op)):
        num = op[idx][0]
        t = op[idx][1]

        if t == 0:
            while num > 0:
                ans = ans * 2 + 2
                num -= 1
        else:
            while num > 0:
                ans = ans * 2 + 1
                num -= 1
    
    return ans

for line in sys.stdin:
    p, q = map(int, line.split(' '))
    print(solve(p, q))
