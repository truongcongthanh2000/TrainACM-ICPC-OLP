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
const int INF = 1e9 + 100;
const long double EPS = 1e-9;
const int BLOCK = 550;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 1e6 + 100;
const int MOD = 998244353;

using u64 = uint64_t;
using u128 = __uint128_t;

struct DisjointSetUnion {  /// Base 1th or Base 0th
    /// if u is root then p[u] < 0 and |p[u]| is size of the Set that u is root
    /// if u is not root then p[u] = x and x, u are belong the same Set
    int n;
    vector<int> p;
    DisjointSetUnion() {};
    DisjointSetUnion(int _n) {
        n = _n;
        p.assign(n + 7, -1);  /// p[i] = -1 for all i
    }

    int find_root(int u) {              /// find the root in the Set contain u
        if (p[u] < 0) return u;         /// u is root
        return p[u] = find_root(p[u]);  /// get the root and jump
    }

    void Union(int u, int v) {
        int x = find_root(u);
        int y = find_root(v);
        if (x == y) return;
        if (p[x] > p[y]) swap(x, y);  /// small Set point to big Set, p[x] > p[y] so |p[x]| < |p[y]|
        p[x] += p[y];
        p[y] = x;
    }

    bool sameSet(int u, int v) {
        return find_root(u) == find_root(v);
    }

    int numSet() {
        int res = 0;
        for (int i = 1; i <= n; i++) res += p[i] < 0;
        return res;
    }
};

bool mark[401][200010];

void sol() {
    /* d[u][v] = min distance from u to v
     for each min distance k, list all (u, v) which d(u, v) = k,
        it's build some connected component -> we can traverse from any node to any node in connected component (*)
      in the query s1, s2, ... , sc, merge all connected component for each d(u, v) = s_i -> it build some connected component
        check exists 1 connect component that contains all d(u, v) cover all value in s_1, s2, ..., s_c
    */
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> d(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) d[i][i] = 0;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        d[u][v] = min(d[u][v], w);
        d[v][u] = d[u][v];
    }
    // floyd
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    // list all distance;
    vector<int> list_d;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            list_d.push_back(d[i][j]);
        }
    }
    sort(list_d.begin(), list_d.end());
    list_d.resize(unique(list_d.begin(), list_d.end()) - list_d.begin());
    // prepare all connected component for each d(u, v)
    m = (int)list_d.size();
    vector<vector<pair<int, int>>> adj(m);
    vector<DisjointSetUnion> set_dsu(m, DisjointSetUnion(n));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int id = lower_bound(list_d.begin(), list_d.end(), d[i][j]) - list_d.begin();
            if (!set_dsu[id].sameSet(i, j)) {
                adj[id].push_back({i, j});
                set_dsu[id].Union(i, j);
            }
        }
    }

    auto get_ans = [&](vector<int> &s, int c) {
        // check exists s(i) that not have any d(u, v) = s(i), ortherwise move s(i) to id in list d(u, v)
        for (int i = 0; i < c; i++) {
            int id = lower_bound(list_d.begin(), list_d.end(), s[i]) - list_d.begin();
            if (id == m || list_d[id] != s[i]) {
                return "No";
            }
            s[i] = id;
        }
        /*/ merge all connected component for each d(u, v) = s_i -> it build some connected component
            check exists 1 connect component that contains all d(u, v) cover all value in s_1, s2, ..., s_c
        */
        DisjointSetUnion dsu(n);
        for (int i = 0; i < c; i++) {
            for (auto [u, v] : adj[s[i]]) {
                dsu.Union(u, v);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < c; j++) mark[i][j] = false;
        }
        for (int i = 0; i < c; i++) {
            for (auto [u, v] : adj[s[i]]) {
                int root = dsu.find_root(u);
                mark[root][i] = true;
            }
        }
        for (int i = 0; i < n; i++) {
            bool all = true;
            for (int j = 0; j < c && all; j++) {
                if (!mark[i][j]) {
                    all = false;
                }
            }
            if (all) {
                return "Yes";
            }
        }
        return "No";
    };

    while (q--) {
        int c;
        cin >> c;
        vector<int> s(c);
        cin >> s;
        cout << get_ans(s, c) << ' ';
    }
    cout << '\n';
}

void solve() {
    clock_t start, end;
    start = clock();
    int T = 1;
    cin >> T;
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
