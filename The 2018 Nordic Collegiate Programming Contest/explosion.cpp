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
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

void open_file() {
    #ifdef THEMIS
        freopen(INP ".inp","r",stdin);
        freopen(OUT ".out","w",stdout);
    #endif // THEMIS
}

const int maxN = 2e5 + 1000;

void sol() {
    int n, m, d;
    cin >> n >> m >> d;

    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    typedef pair<vector<int>, vector<int> > i2;
    map<i2, double> dp;
    map<i2, int> used;

    int sa = 0, sb = 0;
    int da = 0, db = 0;
    for (int i = 0; i < n; i++) {
        sa += a[i];
        da += a[i] > 0;
    }
    for (int i = 0; i < m; i++) {
        sb += b[i];
        db += b[i] > 0;
    }
    function<double(vector<int> &, vector<int> &, int, int, int, int, int)> F = [&](vector<int> &a, vector<int> &b, int sa, int sb, int da, int db, int d) {
        if (sb == 0 || d >= sa + sb) return 1.0;
        if (d < sb) return 0.0;
        if (used[{a, b}]++) return dp[{a, b}];
        double &res = dp[{a, b}];
        res = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] > 0) {
                vector<int> va = a;
                va[i] -= 1;
                sort(va.begin(), va.end());
                double val = F(va, b, sa - 1, sb, da - (a[i] == 1), db, d - 1);
                res += F(va, b, sa - 1, sb, da - (a[i] == 1), db, d - 1);
            }
        }
        for (int i = 0; i < m; i++) {
            if (b[i] > 0) {
                vector<int> vb = b;
                vb[i] -= 1;
                sort(vb.begin(), vb.end());
                double val = F(a, vb, sa, sb - 1, da, db - (b[i] == 1), d - 1);
                res += val;
            }
        }
        res /= da + db;
        return res;
    };
    cout << fixed << setprecision(10) << F(a, b, sa, sb, da, db, d);
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
    ///srand(time(nullptr));
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    open_file();
    solve();
}
