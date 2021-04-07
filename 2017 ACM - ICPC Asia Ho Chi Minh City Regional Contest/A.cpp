#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 311;
const double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 2e6 + 10;

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

int fact[maxN];
void precalc() {
    fact[0] = 1;
    for (int i = 1; i < maxN; i++) fact[i] = 1LL * fact[i - 1] * i % MOD;
}

int nCk(int n, int k) {
    if (k > n) return 0;
    int TS = fact[n];
    int MS = 1LL * fact[k] * fact[n - k] % MOD;
    return 1LL * TS * inverse(MS) % MOD;
}
void sol() {
    precalc();
    int R, W, d;
    cin >> R >> W >> d;
    int res = 0;
    for (int i = 0; i <= W + 1; i++) {
        if (d * i > W + R) break;
        int cost = 1LL * nCk(W + 1, i) * nCk(W + R - d * i - i, W) % MOD;
        if (i & 1) res = (res - cost + MOD) % MOD;
        else res = (res + cost) % MOD;
    }
    cout << res;
}

void solve() {
    int T;
    //cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        ///cout << "Case #" << TestCase << '\n';
        sol();
    }
}
int main(int argc,char *argv[]) {
    //srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
