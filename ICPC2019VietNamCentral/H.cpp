#include <bits/stdc++.h>

using namespace std;

void doc() {
    freopen("OB.inp", "r", stdin);
    freopen("OB.out", "w", stdout);
}
const int module = 666777;
int n, k;
struct mt {
    int c[50][50];
    mt() {
        memset(c, 0, sizeof(c));
    }
};
mt nhan(mt a, mt b) {
    mt c;
    for (int u = 0; u <= k; u++) {
        for (int i = 0; i <= k; i++) {
            for (int j = 0; j <= k; j++) {
                int val = 1LL * a.c[i][u] * b.c[u][j] % module;
                c.c[i][j] = (c.c[i][j] + val) % module;
            }
        }
    }
    return c;
}
mt Get(int n, mt a) {
    mt Res;
    for (int i = 0; i <= k; i++) Res.c[i][i] = 1;
    for (; n; n = n >> 1, a = nhan(a, a)) {
        if (n & 1) Res = nhan(Res, a);
    }
    return Res;
}
void solve() {
    cin >> n >> k;
    k = min(k, n);
    mt a;
    /*
        1 1 1 1
        1 0 0 0
        0 1 0 0
        0 0 1 0
    */
    for (int i = 0; i <= k; i++) a.c[0][i] = 1;
    for (int i = 1; i <= k; i++) a.c[i][i - 1] = 1;
    a = Get(n, a);
    int Res = (a.c[0][0] + a.c[0][1]) % module;
    cout << Res;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    //doc();
    solve();
}
