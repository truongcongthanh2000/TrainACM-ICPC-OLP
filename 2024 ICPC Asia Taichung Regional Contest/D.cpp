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
    int n, m;
    cin >> n >> m;
    auto id = [&](int x, int y) {
        return x * m + y;
    };
    vector<string> s(n);
    cin >> s;
    vector<vector<pair<int, int>>> adj(n * m);
    int start = 0, end = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == 'S') start = id(i, j);
            if (s[i][j] == 'T') end = id(i, j);
            if (s[i][j] != '#') {
                int u = id(i, j);
                for (int dir = 0; dir < 4; dir++) {
                    int x = i + dx[dir];
                    int y = j + dy[dir];
                    if (x >= 0 && x < n && y >= 0 && y < m && s[x][y] != '#') {
                        adj[u].push_back({id(x, y), dir});
                    }
                }
            }
        }
    }
    vector<vector<vector<int>>> d(n * m, vector<vector<int>>(4, vector<int>(4, INF)));
    d[start][0][0] = 0;
    typedef pair<int, array<int, 3>> i2;
    priority_queue<i2, vector<i2>, greater<i2>> Q;
    Q.push({0, {start, 0, 0}});
    while (Q.size() != 0) {
        i2 A = Q.top(); Q.pop();
        int du = A.first, u = A.second[0], dir = A.second[1], k = A.second[2];
        if (du != d[u][dir][k]) continue;
        for (auto [v, dir_v] : adj[u]) {
            int nk = (dir == dir_v ? k + 1 : 1);
            if (nk <= 3) {
                if (d[v][dir_v][nk] > du + 1) {
                    d[v][dir_v][nk] = du + 1;
                    Q.push({du + 1, {v, dir_v, nk}});
                }
            }
        }
    }
    int ans = INF;
    for (int dir = 0; dir < 4; dir++) {
        for (int i = 0; i < 4; i++) {
            ans = min(ans, d[end][dir][i]);
        }
    }
    cout << (ans == INF ? -1 : ans) << '\n';
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
