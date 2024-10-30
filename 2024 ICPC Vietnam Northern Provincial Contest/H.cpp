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
const int BLOCK = 330;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

const int maxN = 1e6 + 100;
const int MOD = 1e9 + 7;

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

struct GeneralMatching {
    GeneralMatching(int _n) : n(_n), match(_n, -1), g(_n), timer(-1), label(_n), parent(_n), orig(_n), aux(_n, -1) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int get_match() {
        for (int i = 0; i < n; i++) {
            if (match[i] == -1) bfs(i);
        }
        int res = 0;
        for (int i = 0; i < n; i++) {
            if (match[i] >= 0) ++res;
        }
        return res / 2;
    }

    int n;
    vector<int> match;

   private:
    int lca(int x, int y) {
        for (timer++;; swap(x, y)) {
            if (x == -1) continue;
            if (aux[x] == timer) return x;
            aux[x] = timer;
            x = (match[x] == -1 ? -1 : orig[parent[match[x]]]);
        }
    }

    void blossom(int v, int w, int a) {
        while (orig[v] != a) {
            parent[v] = w;
            w = match[v];
            if (label[w] == 1) {
                label[w] = 0;
                q.push_back(w);
            }
            orig[v] = orig[w] = a;
            v = parent[w];
        }
    }

    void augment(int v) {
        while (v != -1) {
            int pv = parent[v], nv = match[pv];
            match[v] = pv;
            match[pv] = v;
            v = nv;
        }
    }

    int bfs(int root) {
        fill(label.begin(), label.end(), -1);
        iota(orig.begin(), orig.end(), 0);
        q.clear();
        label[root] = 0;
        q.push_back(root);
        for (int i = 0; i < (int)q.size(); ++i) {
            int v = q[i];
            for (auto x : g[v]) {
                if (label[x] == -1) {
                    label[x] = 1;
                    parent[x] = v;
                    if (match[x] == -1) {
                        augment(x);
                        return 1;
                    }
                    label[match[x]] = 0;
                    q.push_back(match[x]);
                } else if (label[x] == 0 && orig[v] != orig[x]) {
                    int a = lca(orig[v], orig[x]);
                    blossom(x, v, a);
                    blossom(v, x, a);
                }
            }
        }
        return 0;
    }

   private:
    vector<vector<int>> g;
    int timer;
    vector<int> label, parent, orig, aux, q;
};

void sol() {
    int n, m;
    cin >> n >> m;
    DisjointSetUnion dsu(n);
    vector<pair<int, int>> e(m);
    for (int i = 0; i < m; i++) {
        cin >> e[i].first >> e[i].second;
        dsu.Union(e[i].first, e[i].second);
    }
    vector<int> d(n + 1, 0);
    vector<int> special(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int root = dsu.find_root(e[i].first);
        d[root]++;
        if (abs(e[i].first - e[i].second) == 1) {
            special[root] = 1;
        }
    }

    GeneralMatching gm(n);
    for (int i = 1; i < n; i++) {
        int u = dsu.find_root(i);
        int v = dsu.find_root(i + 1);
        if (!special[u] && !special[v] && d[u] + 1 == -dsu.p[u] && d[v] + 1 == -dsu.p[v]) {
            gm.add_edge(u - 1, v - 1);
        }
    }
    int sz_special = 0;
    for (int i = 1; i <= n; i++) {
        if (dsu.find_root(i) == i && !special[i] && d[i] + 1 == -dsu.p[i]) {
            sz_special++;
        }
    }
    int cost = gm.get_match();
    cout << cost + sz_special - 2 * cost << '\n';
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
