n, k = [int(x) for x in input().split()]
res = []
for d in [9, 8, 7, 6, 5, 4, 3, 2]:
    while n % d == 0:
        res.append(d)
        n //= d
if len(res) > k or n != 1:
    print(-1)
else:
    res += [1] * (k - len(res))
    res.sort()
    for i in res:
    	print(i,end='')
