#pragma GCC diagnostic ignored "-Wunused-parameter"
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "solve"
#define OUT "solve"

const long long INF_LL = 8e18;
const int INF = 1e9 + 100;
const int MOD = 1e9 + 7;
//const int Base = 311;9
const long double EPS = 1e-10;
const int BLOCK = 1000;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 1e7 + 100;

struct mt {
    vector<vector<double> > c;
    mt(int _n = 1, int _m = 1) {
        c = vector<vector<double> > (_n, vector<double>(_m, 0));
    }
};

mt nhan(mt a, mt b) {
    int n = (int)a.c.size();
    mt c(n, n);
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                double cost = a.c[i][k] * b.c[k][j];
                c.c[i][j] += cost;
            }
        }
    }
    return c;
}

mt power(mt a, int n) {
    int sz = (int)a.c.size();
    mt ans(sz, sz);
    for (int i = 0; i < sz; i++) ans.c[i][i] = 1;
    for (; n; n >>= 1, a = nhan(a, a)) {
        if (n & 1) {
            ans = nhan(ans, a);
        }
    }
    return ans;
}

void sol(){
    int n, m;
    cin >> n >> m;
    mt a(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> a.c[i][j];
    }
    a = power(a, m);
    for (int i = 0; i < n; i++) {
        cout << fixed << setprecision(10) << a.c[0][i] << ' ';
    }
}

void solve() {
    clock_t begin = clock();
    int T;
//    cin >> T;
    T = 1;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        //cout << "Case #" << TestCase << ":" << ' ';
        //cout << "Test " << TestCase << ": ";
        sol();
    }
    clock_t end = clock();
    cerr << "Time: " << fixed << setprecision(10) << (double)(end - begin) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc,char *argv[]) {
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
