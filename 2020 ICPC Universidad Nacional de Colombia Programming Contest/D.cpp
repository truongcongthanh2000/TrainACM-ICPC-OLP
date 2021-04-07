#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
const int Base = 30;
const long double EPS = 1e-9;
const int BLOCK = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 2e3 + 100;
vector<long long> x;

vector<long long> join(vector<long long> a, vector<long long> b) {
    int m = a.size();
    vector<long long> res(m, 0);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            res[(i + j) % m] += a[i] * b[j] % MOD;
            res[(i + j) % m] %= MOD;
        }
    }
    return res;
}

vector<long long> rec(vector<long long> a, long long k){
//    int m = (int)a.size();
//    vector<long long> res(m, 1LL);
//    for (; k; k >>= 1, a = join(a, a)) {
//        if (k & 1) res = join(res, a);
//    }
//    return res;
    if (k == 1) {
        return x;
    }
    vector<long long> y = rec(a, k / 2);
    if (k % 2 == 1) {
        return join(join(y, y), a);
    }
    return join(y, y);
}

long long Pow(long long b, long long e = MOD - 2) {
    if (e == 0) return 1;
    long long x = Pow(b, e / 2);
    if (e % 2 == 0) return x * x % MOD;
    return (x * x % MOD) * b % MOD;
}

void sol() {
    int n, k, m; cin >> n >> k >> m;
    x = vector<long long>(m, 0);
    for (int i = 1; i <= k; ++i) {
        if (i % m != 0) x[i % m]++;
    }
    vector<long long> res = rec(x, n);
    long long tot = 0;
    //for (int i = 0; i < m; ++i) cout << res[i] << ' ';
    //cout << '\n';
    for (int i = 0; i < m; ++i) tot = (tot + res[i]) % MOD;
    cout << res[0] * Pow(tot) % MOD;
    //cout << res[0] * nhan(tot, MOD - 1, MOD) % MOD;
}
void solve() {
    int T;
    ///cin >> T;
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
 
