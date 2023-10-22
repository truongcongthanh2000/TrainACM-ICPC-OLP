#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define INP "input"
#define OUT "output"

/* some template */
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& a) {
    out << (int)a.size() << '\n';
    for (const auto& v : a) out << v << ' ';
    out << endl;
    return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<vector<T>>& a) {
    out << (int)a.size() << '\n';
    for (const auto& v : a) {
        for (const auto& value : v) out << value << ' ';
        out << endl;
    }
    return out;
}

template <typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& v) {
    for (auto& x : v) is >> x;
    return is;
}
/* end template */

const long long INF_LL = 1e18;
const int INF = 2e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 2e5 + 100;
const int MOD = 1e9 + 7;

void sol() {
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    cin >> s;
    auto deg = [&](int x, int y) {
        vector<pair<int, int>> ans;
        for (int h = 1; h < 3; h++) {
            int u = x + dx[h];
            int v = y + dy[h];
            if (u >= 0 && u < n && v >= 0 && v < m && s[u][v] == '.') {
                ans.push_back({u, v});
            }
        }
        return ans;
    };
    auto id = [&](int x, int y) {
        return x * m + y;
    };
    vector<vector<int>> adj(n * m);
    int n_spaces = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == '.') {
                for (auto [u, v] : deg(i, j)) {
                    int s = id(i, j);
                    int t = id(u, v);
                    adj[s].push_back(t);
                    adj[t].push_back(s);
                }
                n_spaces++;
            }
        }
    }
    long long ans = 1LL * n_spaces * (n_spaces - 1);
    vector<int> low(n * m, 0), order(n * m, 0);
    function<void(int, int)> dfs = [&](int u, int pa) {
        static int time = 0;
        static stack<int> stk;
        stk.push(u);
        low[u] = order[u] = ++time;
        for (int v : adj[u]) {
            if (v != pa) {
                if (order[v] == 0) {
                    dfs(v, u);
                    low[u] = min(low[u], low[v]);
                    if (pa == -1 || low[v] >= order[u]) {
                        int vertice, d = 1;
                        do {
                            vertice = stk.top();
                            stk.pop();
                            d++;
                        } while (vertice != v);
                        ans -= 1LL * d * (d - 1);
                    }
                } else {
                    low[u] = min(low[u], order[v]);
                }
            }
        }
    };
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == '.' && order[id(i, j)] == 0) {
                dfs(id(i, j), -1);
            }
        }
    }
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
        // cerr << "Processing test = " << TestCase << '\n';
        // cout << "Case #" << TestCase << ": ";
        sol();
        // if (T) cout << '\n';
    }
    end = clock();
    cerr << "Time = " << (double)(end - start) / (double)CLOCKS_PER_SEC << '\n';
}

int main(int argc, char* argv[]) {
    // srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
