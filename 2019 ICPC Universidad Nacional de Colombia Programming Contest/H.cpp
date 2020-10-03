#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 1e17;
const int INF = 1e9 + 100;
const long long MOD = 1e15 + 37;
const int Base = 30;
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

const int maxN = 5e5 + 10;

long long pw[maxN];

void DFS(int pos, long long hash, vector<long long> &value, vector<string> &a, int limits, int n) {
    if (pos == limits) {
        value.push_back(hash);
        return;
    }
    for (int i = 0; i < 3; i++) {
        long long next_hash = (hash + pw[n - pos - 1] * (int)a[i][pos]) % MOD;
        DFS(pos + 1, next_hash, value, a, limits, n);
    }
}

long long get(vector<string> &c) {
    int n = (int)c[0].size();
    int m = n / 2;
    vector<long long> a, b;
    DFS(0, 0, a, c, m, n);
    DFS(m, 0, b, c, n, n);
    sort(a.begin(), a.end());
    sort(b.begin(), b.end(), greater<long long>());
    long long res = (a[0] + b.back()) % MOD;
    int L = 0;
    for (long long x : b) {
        while (L < (int)a.size() && x + a[L] < MOD) L++;
        if (L < (int)a.size()) res = min(res, (x + a[L]) % MOD);
    }
    return res;
}

void sol() {
    pw[0] = 1;
    for (int i = 1; i < maxN; i++) pw[i] = pw[i - 1] * 127 % MOD;
    int n, m;
    cin >> n >> m;
    vector<string> a(3), b(3);
    for (int i = 0; i < 3; i++) cin >> a[i];
    for (int i = 0; i < 3; i++) cin >> b[i];
    long long res_a = get(a);
    long long res_b = get(b);
    //cout << res_a << " " << res_b << '\n';
    if (res_a < res_b) cout << "Owls";
    if (res_a > res_b) cout << "Goats";
    if (res_a == res_b) cout << "Tie";
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
