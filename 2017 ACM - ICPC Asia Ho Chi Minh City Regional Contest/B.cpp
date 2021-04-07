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

int power(int a, int n, int MOD) {
    int res = 1;
    for (; n; n >>= 1, a = 1LL * a * a % MOD) {
        if (n & 1) {
            res = 1LL * res * a % MOD;
        }
    }
    return res;
}
int inverse(int a, int MOD) {
    return power(a, MOD - 2, MOD);
}

typedef pair<int, int> i2;
i2 fact[maxN];
void sol() {
    int n, m;
    cin >> n >> m;
    fact[0] = {1, 0};
    for (int i = 1; i <= n; i++) {
        int mu = 0;
        int j = i;
        while (j % m == 0) {
            mu++;
            j /= m;
        }
        fact[i] = {1LL * fact[i - 1].first * j % m, fact[i - 1].second + mu};
    }
    auto nCk = [&](int n, int k) -> int {
        if (k > n) return 0;
        i2 TS = fact[n];
        i2 MS = i2(1LL * fact[k].first * fact[n - k].first % m, fact[k].second + fact[n - k].second);
        int res = 1LL * TS.first * inverse(MS.first, m) % m;
        if (TS.second > MS.second) return 0;
        return res;
    };
    int f0 = 1, f1 = 2;
    for (int i = 2; i <= n; i++) {
        int f2 = (f0 + f1) % m;
        f0 = f1;
        f1 = f2;
    }
    int res = f1;
    if (n % 2 == 0 && n > 2) {
        res = (res + nCk(n, n / 2)) % m;
        int cost = nCk(n - n / 2 + 1, n / 2);
        res = (res - cost + m) % m;
    }
    cout << res << '\n';
}

void solve() {
    int T;
    cin >> T;
    //T = 1;
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
