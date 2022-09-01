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

int power(int a, int n, int MOD) {
    int ans = 1 % MOD;
    for (; n; n >>= 1, a = 1LL * a * a % MOD) {
        if (n & 1) {
            ans = 1LL * ans * a % MOD;
        }
    }
    return ans;
}

int n, m;
int D[maxN];
int b[maxN][20];
vector<int> adj[maxN];
int down[maxN], up[maxN][20], w[maxN];

void DFS(int u, int pa) {
    down[u] = (1LL * down[pa] * 10 + w[u]) % m;

    for (int i = 0; i <= 18; i++) {
        int v = b[u][i];
        if (v == 0) break;
        b[u][i + 1] = b[v][i];
        up[u][i + 1] = (1LL * up[u][i] * power(10, 1 << i, m) + up[v][i]) % m;
    }

    for (int v : adj[u]) {
        if (v != pa) {
            up[v][0] = w[u];
            D[v] = D[u] + 1;
            b[v][0] = u;
            DFS(v, u);
        }
    }
}

int LCA(int u, int v) {
    if (D[u] < D[v]) swap(u, v);
    int k = D[u] - D[v];
    for (int i = 18; i >= 0; i--) {
        if (k >= (1 << i)) {
            k -= (1 << i);
            u = b[u][i];
        }
    }
    if (u == v) return u;
    int res = 0;
    for (int i = 18; i >= 0; i--) {
        if (b[u][i] != b[v][i]) {
            u = b[u][i];
            v = b[v][i];
        } else
            res = b[u][i];
    }
    return res;
}

int get_down(int root, int u) {
    int k = D[u] - D[root];
    int ans = w[u];
    for (int i = 18; i >= 0; i--) {
        if (k >= (1 << i)) {
            k -= (1 << i);
            ans = (1LL * ans * power(10, 1 << i, m) + up[u][i]) % m;
            u = b[u][i];
        }
    }
    return ans;
}

void sol() {
    int q;
    cin >> n >> m >> q;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        w[i] %= m;
    }
    DFS(1, 0);
    while (q--) {
        int u, v;
        cin >> u >> v;
        int root = LCA(u, v);
        int w_uroot = get_down(root, u);
        int w_rootv = (down[v] - 1LL * down[root] * power(10, D[v] - D[root], m) % m + m) % m;
        cout << (1LL * w_uroot * power(10, D[v] - D[root], m) + w_rootv) % m << '\n';
    }
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
