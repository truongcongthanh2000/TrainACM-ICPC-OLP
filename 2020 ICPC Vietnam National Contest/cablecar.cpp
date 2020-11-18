#include <bits/stdc++.h>

using namespace std;

void doc() {
    #ifdef THEMIS
        freopen("solve.inp", "r", stdin);
        freopen("solve.out", "w", stdout);
    #endif
}

const int maxN = 1e3 + 100;
const int INF = 1e6 + 100;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
const int maxv = 2e6 + 10;
const int maxe = 1e7 + 10;
clock_t Begin;

void sol() {
    int n, k;
    cin >> n >> k;
    for (int m = 1; m <= n; m++) {
        int q = n / m;
        int r = n - q * m;
        cerr << m << " " << q << " " << r << '\n';
        vector<vector<int> > a(m, vector<int>(q + 1, -1));
        for (int j = 0, t = 1; j <= q; j++) {
            for (int i = 0; i < m; i++) {
                if (t <= n) a[i][j] = t++;
            }
        }
        typedef pair<int, int> i2;
        vector<i2> c, d;
        for (int x = k, j = 0; j <= q; j++) {
            for (int i = 0; i < m - 1; i++) {
                if (x > 0) {
                    if (a[i][j] != -1 && a[i + 1][j] != -1) {
                        c.push_back({a[i][j], a[i + 1][j]});
                        x--;
                    }
                }
            }
        }
        for (int x = k, i = 0; i < m; i++) {
            for (int j = 0; j < q; j++) {
                if (x > 0 && a[i][j + 1] != -1) {
                    d.push_back({a[i][j], a[i][j + 1]});
                    x--;
                }
            }
        }
        if ((int)c.size() == k && (int)d.size() == k) {
            cout << "YES" << '\n';
            for (auto it : c) cout << it.first << " " << it.second << '\n';
            for (auto it : d) cout << it.first << " " << it.second << '\n';
            return;
        }
    }
    cout << "NO";
}

void solve() {
    Begin = clock();
    int T;
    //cin >> T;
    T = 1;
    while (T--) {
        sol();
    }
    cerr << fixed << setprecision(10) << (double)(clock() - Begin) / (double)CLOCKS_PER_SEC << '\n';
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
    doc();
    solve();
}
