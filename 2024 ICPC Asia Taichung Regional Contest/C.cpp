#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <immintrin.h>

using namespace std;

#define INP "input"
#define OUT "output"

/* some template */
template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &a) {
    out << (int)a.size() << '\n';
    for (const auto &v : a) out << v << ' ';
    out << endl;
    return out;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<vector<T>> &a) {
    out << (int)a.size() << '\n';
    for (const auto &v : a) {
        for (const auto &value : v) out << value << ' ';
        out << endl;
    }
    return out;
}

template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
    for (auto &x : v) is >> x;
    return is;
}
/* end template */

const long long INF_LL = 1e18;
const int INF = 1e9 + 100;
const long double EPS = 1e-9;
const int BLOCK = 330;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 1e6 + 100;
const int MOD = 998244353;

void sol() {
    int n;
    cin >> n;
    int a[n][n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int z = 0; z < n; z++) {
                cin >> a[i][j][z];
            }
        }
    }
    vector<vector<int>> adj(1 << n);
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (!((mask >> i) & 1)) {
                adj[mask].push_back(i);
            }
        }
    }
    vector<vector<int>> dp(1 << n, vector<int>(1 << n, INF));
    dp[0][0] = 0;
    for (int x = 0; x < n; x++) {
        vector<vector<int>> ndp(1 << n, vector<int>(1 << n, INF));
        for (int m1 = 0; m1 < (1 << n); m1++) {
            for (int m2 = 0; m2 < (1 << n); m2++) {
                if (dp[m1][m2] != INF) {
                    for (int u : adj[m1]) {
                        for (int v : adj[m2]) {
                            int nm1 = m1 ^ (1 << u);
                            int nm2 = m2 ^ (1 << v);
                            ndp[nm1][nm2] = min(ndp[nm1][nm2], dp[m1][m2] + a[x][u][v]);
                        }
                    }
                }
            }
        }
        swap(ndp, dp);
    }
    cout << dp[(1 << n) - 1][(1 << n) - 1] << '\n';
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    // cin >> T;
    int TestCase = 0;
    while (T--) {
        TestCase += 1;
        cerr << "Processing test = " << TestCase << '\n';
        // cout << "Case #" << TestCase << ": ";
        sol();
        // if (T) cout << '\n';
    }
    end = clock();
    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc, char *argv[]) {
    // srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
