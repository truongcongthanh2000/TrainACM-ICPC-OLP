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
const int dx[3] = {1, 0, 1};
const int dy[3] = {
    0,
    1,
    1,
};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 2e5 + 100;
const int MOD = 998244353;

int D[maxN];
int b[maxN][20];
long long F[maxN];
typedef pair<int, int> i2;
vector<i2> adj[maxN];
void DFS(int u, int pa) {
    for (int i = 0; i <= 18; i++) {
        int v = b[u][i];
        if (v == 0) break;
        b[u][i + 1] = b[v][i];
    }
    for (auto [v, w] : adj[u]) {
        if (v != pa) {
            D[v] = D[u] + 1;
            F[v] = F[u] + w;
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

void sol() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, 1});
        adj[v].push_back({u, 1});
    }
    DFS(1, 0);
    auto ok = [&](int x, int y, int z) {  // check path x-y contains vertex z
        int root = LCA(x, y);
        // z must be belong to path x->root or belong to path y->root
        return LCA(root, z) == root && (LCA(z, x) == z || LCA(z, y) == z);
    };
    while (q--) {
        int x, y, z;
        cin >> x >> y >> z;
        if (ok(x, z, y))
            cout << "YES" << '\n';
        else
            cout << "NO" << '\n';
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

int main(int argc, char *argv[]) {
    // srand(time(nullptr));
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
