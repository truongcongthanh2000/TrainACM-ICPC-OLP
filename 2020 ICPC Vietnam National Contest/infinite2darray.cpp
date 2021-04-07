#include <bits/stdc++.h>

using namespace std;

void doc() {
    #ifdef THEMIS
        freopen("solve.inp", "r", stdin);
        freopen("solve.out", "w", stdout);
    #endif
}

const int maxN = 3e6 + 100;
const int MOD = 1e9 + 7;
const int INF = 1e6 + 100;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

int w[maxN];
int fi[maxN];
int fact[maxN];

int power(int a, int n) {
    int res = 1;
    for (; n; n >>= 1, a = 1LL * a * a % MOD) {
        if (n & 1) {
            res = 1LL * res * a % MOD;
        }
    }
    return res;
}
int inverse(int a) {
    return power(a, MOD - 2);
}
int nCk(int n, int k) {
    if (k > n) return 0;
    int TS = fact[n];
    int MS = 1LL * fact[k] * fact[n - k] % MOD;
    return 1LL * TS * inverse(MS) % MOD;
}
void sol() {
    int x, y;
    cin >> x >> y;
    if (x < y) swap(x, y);
    fi[0] = 0;
    fi[1] = 1;
    for (int i = 2; i < maxN; i++) fi[i] = (fi[i - 1] + fi[i - 2]) % MOD;
    fact[0] = 1;
    for (int i = 1; i < maxN; i++) fact[i] = 1LL * fact[i - 1] * i % MOD;
    int res = 0;
    for (int t = 0; t <= y; t++) {
        int cost = 1LL * fi[t] * nCk(x + y - 1 - t, x - 1) % MOD;
        res = (res + cost) % MOD;
    }
    for (int t = 0; t <= x; t++) {
        int cost = 1LL * fi[t] * nCk(x - 1 + y - t, y - 1) % MOD;
        res = (res + cost) % MOD;
    }
    cout << res;
}

void solve() {
    int T;
    //cin >> T;
    T = 1;
    while (T--) {
        sol();
    }
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    doc();
    solve();
}
