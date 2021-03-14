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

pair<int, int> calc(vector<vector<int> > a) {
    int n = (int)a.size();
    int m = (int)a[0].size();
    vector<vector<int> > s(n, vector<int>(m, 0));
    s[0][0] = a[0][0];
    for (int i = 1; i < m; i++) s[0][i] = s[0][i - 1] + a[0][i];
    for (int i = 1; i < n; i++) s[i][0] = s[i - 1][0] + a[i][0];
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
        }
    }
    auto sum = [&](int x, int y, int u, int v) {
        int ans = s[u][v];
        if (x) ans -= s[x - 1][v];
        if (y) ans -= s[u][y - 1];
        if (x && y) ans += s[x - 1][y - 1];
        return ans;
    };

    vector<vector<int> > mx_f1(n, vector<int>(m, -INF));

    int ans1 = -INF;
    for (int i = 0; i < n; i++) {
        for (int r = i; r < n; r++) {
            int mn = 0;
            int s = 0;
            for (int j = m - 1; j >= 0; j--) {
                int cost = sum(i, j, r, j);
                s += cost;
                mx_f1[i][j] = max(mx_f1[i][j], s - mn);
                mn = min(mn, s);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans1 = max(ans1, mx_f1[i][j]);
        }
    }

    vector<vector<int> > mx_f2(n, vector<int>(m, -INF));

    for (int i = 0; i < n; i++) {
        for (int r = i; r < n; r++) {
            int mn = 0;
            int s = 0;
            for (int j = 0; j < m; j++) {
                int cost = sum(i, j, r, j);
                s += cost;
                mx_f2[r][j] = max(mx_f2[r][j], s - mn);
                mn = min(mn, s);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i > 0) mx_f2[i][j] = max(mx_f2[i][j], mx_f2[i - 1][j]);
            if (j > 0) mx_f2[i][j] = max(mx_f2[i][j], mx_f2[i][j - 1]);
            if (i && j) mx_f2[i][j] = max(mx_f2[i][j], mx_f2[i - 1][j - 1]);
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            if (i + 1 < n) mx_f1[i][j] = max(mx_f1[i][j], mx_f1[i + 1][j]);
            if (j + 1 < m) mx_f1[i][j] = max(mx_f1[i][j], mx_f1[i][j + 1]);
            if (i + 1 < n && j + 1 < m) mx_f1[i][j] = max(mx_f1[i][j], mx_f1[i + 1][j + 1]);
        }
    }
    int ans2 = -INF;
    for (int i = 0; i + 1 < n; i++) {
        int cost = mx_f1[i + 1][0] + mx_f2[i][m - 1];
        ans2 = max(ans2, cost);
    }
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < m; j++) cerr << a[i][j] << ' ';
//        cerr << '\n';
//    }
//    cerr << "ans: " << ans1 << " " << ans2 << '\n';
    return {ans1, ans2};
}

void sol(){
    int n, m;
    cin >> n >> m;
    vector<vector<int> > a(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cin >> a[i][j];
    }
    int ans = -INF;
    {
        for (int r = 0; r + 1 < n; r++) {
            vector<vector<int> > L1(r + 1, vector<int>(m, 0));
            for (int i = 0; i <= r; i++) {
                for (int j = 0; j < m; j++) L1[i][j] = a[i][j];
            }
            vector<vector<int> > L2(m, vector<int>(r + 1, 0));
            for (int i = 0; i <= r; i++) {
                for (int j = 0; j < m; j++) {
                    L2[j][r - i] = a[i][j];
                }
            }
            vector<vector<int> > R1(n - r - 1, vector<int>(m, 0));
            for (int i = r + 1; i < n; i++) {
                for (int j = 0; j < m; j++) R1[i - r - 1][j] = a[i][j];
            }
            vector<vector<int> > R2(m, vector<int>(n - r - 1));
            for (int i = r + 1; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    R2[j][(n - r - 2) - (i - r - 1)] = a[i][j];
                }
            }
            auto ans_L1 = calc(L1);
            auto ans_L2 = calc(L2);
            auto ans_R1 = calc(R1);
            auto ans_R2 = calc(R2);
            ans = max(ans, max(ans_L1.first, ans_L2.first) + max(ans_R1.second, ans_R2.second));
            ans = max(ans, max(ans_L1.second, ans_L2.second) + max(ans_R1.first, ans_R2.first));
        }
    }
    {
        for (int c = 0; c + 1 < m; c++) {
            vector<vector<int> > L1(n, vector<int>(c + 1, 0));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j <= c; j++) L1[i][j] = a[i][j];
            }
            vector<vector<int> > L2(c + 1, vector<int>(n, 0));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j <= c; j++) L2[c - j][i] = a[i][j];
            }
            vector<vector<int> > R1(n, vector<int>(m - c - 1, 0));
            for (int i = 0; i < n; i++) {
                for (int j = c + 1; j < m; j++) R1[i][j - c - 1] = a[i][j];
            }
            vector<vector<int> > R2(m - c - 1, vector<int>(n, 0));
            for (int i = 0; i < n; i++) {
                for (int j = c + 1; j < m; j++) R2[(m - c - 2) - (j - c - 1)][i] = a[i][j];
            }
            auto ans_L1 = calc(L1);
            auto ans_L2 = calc(L2);
            auto ans_R1 = calc(R1);
            auto ans_R2 = calc(R2);
            ans = max(ans, max(ans_L1.first, ans_L2.first) + max(ans_R1.second, ans_R2.second));
            ans = max(ans, max(ans_L1.second, ans_L2.second) + max(ans_R1.first, ans_R2.first));
        }
    }
    cout << ans;
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
S
