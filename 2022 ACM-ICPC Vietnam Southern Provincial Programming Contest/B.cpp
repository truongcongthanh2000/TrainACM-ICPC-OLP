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

struct DisjointSetUnion {  /// Base 1th or Base 0th
    /// if u is root then p[u] < 0 and |p[u]| is size of the Set that u is root
    /// if u is not root then p[u] = x and x, u are belong the same Set
    int n;
    vector<int> p;
    DisjointSetUnion(){};
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

struct Tree {
   public:
    Tree(int _n = 0) {
        n = _n;
        adj = vector<vector<pair<int, int>>>(n);
        d = vector<int>(n, 0);

        lg = 0;
        while ((1 << lg) <= n) lg++;

        par = vector<vector<int>>(n, vector<int>(lg, -1));
        f = vector<vector<int>>(n, vector<int>(lg, INF));
    }

    void buildTree() {
        for (int i = 0; i < n; i++) {
            if (par[i][0] == -1) DFS(i, -1);
        }
    }

    void add_Edge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int getCost(int u, int v) {
        int root = LCA(u, v);
        return min(minCost(u, root), minCost(v, root));
    }

   private:
    int n, lg;
    vector<vector<pair<int, int>>> adj;
    vector<vector<int>> par, f;
    vector<int> d;

    void DFS(int u, int parent) {
        for (int i = 0; i < lg - 1; i++) {
            int v = par[u][i];
            if (v == -1) break;
            par[u][i + 1] = par[v][i];
            f[u][i + 1] = min(f[u][i], f[v][i]);
        }

        for (auto [v, w] : adj[u]) {
            if (v != parent) {
                par[v][0] = u;
                f[v][0] = w;
                d[v] = d[u] + 1;
                DFS(v, u);
            }
        }
    }

    int LCA(int u, int v) {
        if (d[u] < d[v]) swap(u, v);
        int k = d[u] - d[v];

        for (int i = lg - 1; i >= 0; i--) {
            if (k >= (1 << i)) {
                k -= (1 << i);
                u = par[u][i];
            }
        }

        if (u == v) return u;

        for (int i = lg - 1; i >= 0; i--) {
            if (par[u][i] != par[v][i]) {
                u = par[u][i];
                v = par[v][i];
            }
        }
        return par[u][0];
    }

    int minCost(int u, int parent) {
        int ans = INF;
        int k = d[u] - d[parent];

        for (int i = lg - 1; i >= 0; i--) {
            if (k >= (1 << i)) {
                ans = min(ans, f[u][i]);
                u = par[u][i];
                k -= (1 << i);
            }
        }
        return ans;
    }
};

struct Query {
    char t;
    int a, b, w;

    Query(){};
    Query(char _t, int _a, int _b, int _w = 0) {
        t = _t;
        a = _a;
        b = _b;
        w = _w;
    };
};

void sol() {
    int n, m, Q;
    cin >> n >> m >> Q;
    vector<array<int, 3>> edges(m);

    for (int i = 0; i < m; i++) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
        edges[i][0]--;
        edges[i][1]--;
    }

    vector<int> id_edges_can_use;
    DisjointSetUnion dsu;
    Tree cur_tree;

    auto build_mst = [&](vector<int>& id_edges, bool firstMst) {
        sort(id_edges.begin(), id_edges.end(), [&](int i, int j) {
            return edges[i][2] > edges[j][2];
        });

        dsu = DisjointSetUnion(n);
        cur_tree = Tree(n);
        for (int id : id_edges) {
            int u = edges[id][0], v = edges[id][1], w = edges[id][2];

            if (dsu.find_root(u) != dsu.find_root(v)) {
                dsu.Union(u, v);
                cur_tree.add_Edge(u, v, w);

                if (firstMst) {
                    id_edges_can_use.push_back(id);
                }
            }
        }
        cur_tree.buildTree();
    };
    vector<int> id(m);
    iota(id.begin(), id.end(), 0);

    build_mst(id, true);

    vector<int> updated_edges;
    vector<Query> q(Q);
    for (int i = 0; i < Q; i++) {
        cin >> q[i].t >> q[i].a >> q[i].b;
        if (q[i].t == 'C') {
            q[i].a--;
            id_edges_can_use.push_back(q[i].a);
            updated_edges.push_back(q[i].a);
        } else {
            q[i].a--;
            q[i].b--;
            cin >> q[i].w;
        }
    }

    sort(updated_edges.begin(), updated_edges.end());
    id.clear();
    for (int i = 0; i < m; i++) {
        if (!std::binary_search(updated_edges.begin(), updated_edges.end(), i)) {
            id.push_back(i);
        }
    }
    build_mst(id, true);

    sort(id_edges_can_use.begin(), id_edges_can_use.end());
    id_edges_can_use.resize(unique(id_edges_can_use.begin(), id_edges_can_use.end()) - id_edges_can_use.begin());

    build_mst(id_edges_can_use, false);
    for (const auto& query : q) {
        if (query.t == 'C') {
            int id = query.a, x = query.b;

            edges[id][2] = x;
            build_mst(id_edges_can_use, false);
        } else {
            int a = query.a, b = query.b, w = query.w;
            if (!dsu.sameSet(a, b)) {
                cout << "NO" << '\n';
                continue;
            }
            if (cur_tree.getCost(a, b) < w)
                cout << "NO" << '\n';
            else
                cout << "YES" << '\n';
        }
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
