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
std::ostream& operator<<(std::ostream& out, const std::vector<vector<T> >& a) {
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
const int INF = 1e9 + 100;
const long double EPS = 1e-6;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

void open_file() {
#ifdef THEMIS
    freopen(INP ".txt", "r", stdin);
    freopen(OUT ".txt", "w", stdout);
#endif  // THEMIS
}

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

void sol() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), par(n);
    cin >> a;
    vector<vector<int> > adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        par[v] = u;
    }

    vector<int> dp(n, 0), root(n, 0), L(n), R(n);
    int order = -1;
    function<void(int, int)> dfs = [&](int u, int r) {
        L[u] = ++order;
        dp[u] += a[u];
        root[u] = r;
        for (int v : adj[u]) {
            if (dp[v] == 0) {
                dp[v] += dp[u];
                dfs(v, r);
            }
        }
        R[u] = order;
    };

    for (int i = 0; i < n; i++) {
        if (dp[i] == 0) dfs(i, i);
    }

    vector<int> v_cc;
    for (int i = 0; i < n; i++) {
        if ((int)adj[i].size() == 0) v_cc.push_back(i);
    }
    int ans = INF;
    for (int i = 0; i < (int)v_cc.size(); i++) {
        for (int j = i + 1; j < (int)v_cc.size(); j++) {
            int u = v_cc[i], v = v_cc[j];
            int w = dp[u] + dp[v];
            if (root[u] == root[v]) {
                while (L[u] > L[v] || R[u] < R[v]) {
                    u = par[u];
                }
                w -= dp[u];
            }
            ans = min(ans, w);
        }
    }
    cout << ans;
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

int main(int argc, char* argv[]) {
    // srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    open_file();
    solve();
    return 0;
}
