#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

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
const int INF = 2e9 + 100;
const long double EPS = 1e-9;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 2e5 + 100;
const int MOD = 998244353;

void sol() {
    // traveling salesman problem
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, int>> p; // list id(x, y) of 'S'
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        for (int j = 0; j < m; j++) {
            if (s[i][j] == 'S') {
                p.push_back({i, j});
            }
        }
    }
    auto bfs = [&](pair<int, int> source, pair<int, int> target) -> int {
        vector<vector<int>> dist(n, vector<int>(m, -1));
        dist[source.first][source.second] = 0;
        queue<pair<int, int>> Q;
        Q.push(source);
        while (Q.size() != 0) {
            pair<int, int> A = Q.front();
            Q.pop();
            int x = A.first, y = A.second;
            for (int h = 0; h < 4; h++) {
                int u = x + dx[h];
                int v = y + dy[h];
                if (u >= 0 && u < n && v >= 0 && v < m && s[u][v] != '#' && dist[u][v] == -1) {
                    dist[u][v] = dist[x][y] + 1;
                    Q.push({u, v});
                }
            }
        }
        return dist[target.first][target.second];
    };
    vector<vector<int>> w(k, vector<int>(k, 0));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            w[i][j] = bfs(p[i], p[j]);
            if (w[i][j] == -1) { // exists pair S-S is not connected
                cout << -1 << '\n';
                return;
            }
        }
    }
    // dp[mask][u]: minimum distance visited all bit 1 in mask and end in vertex u
    vector<vector<int>> dp(1 << k, vector<int>(k, INF));
    for (int i = 0; i < k; i++) {
        dp[1 << i][i] = bfs({0, 0}, p[i]); // distance from start to p[i]
        if (dp[1 << i][i] == -1) { // not connected
            cout << -1 << '\n';
            return;
        }
    }
    for (int mask = 1; mask < (1 << k); mask++) {
        for (int u = 0; u < k; u++) {
            if ((mask >> u) & 1) {
                for (int v = 0; v < k; v++) {
                    int bit = (mask >> v) & 1;
                    if (!bit) {
                        dp[mask ^ (1 << v)][v] = min(dp[mask ^ (1 << v)][v], dp[mask][u] + w[u][v]);
                    }
                }
            }
        }
    }
    int ans = INF;
    for (int u = 0; u < k; u++) ans = min(ans, dp[(1 << k) - 1][u]);
    cout << ans << '\n';
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
