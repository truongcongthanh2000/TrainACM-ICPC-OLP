n, m, k = map(int, input().split())

ans = 0
for g1 in range(max(n // k - m, 0), n // k + 1):
    rem = n - k * g1
    g2 = rem % m
    if g2 == 0:
        g2 = m
    g3 = m - g2 
    mx = (rem + m - 1) // m 
    res = g1 * n - k * g1 * (g1 - 1) // 2
    #print(res)
    res += rem * g2 - mx * g2 * (g2 - 1) // 2
    rem -= mx * g2 
    res += rem * g3 - (mx - 1) * g3 * (g3 - 1) // 2

    ans = max(ans, res)

print(ans)