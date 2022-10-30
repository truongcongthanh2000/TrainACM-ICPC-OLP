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

void sol() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    cin >> a;

    DisjointSetUnion dsu(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        dsu.Union(u, v);
    }

    vector<vector<int> > adj(n);
    for (int i = 0; i < n; i++) {
        int p = dsu.find_root(i);
        adj[p].push_back(a[i]);
    }

    for (int i = 0; i < n; i++) {
        sort(adj[i].begin(), adj[i].end(), greater<int>());
    }

    vector<int> b;
    for (int i = 0; i < n; i++) {
        int p = dsu.find_root(i);

        if ((int)adj[p].size() == 0) continue;

        int j = 0;
        if ((int)b.size() == 0 || b.back() < adj[p][0]) {
            b.push_back(adj[p][0]);
            j = 1;
        }

        int L = (int)b.size() - 1;
        for (int i = j; i < (int)adj[p].size(); i++) {
            while (L > 0 && b[L - 1] >= adj[p][i]) L--;
            b[L] = adj[p][i];
        }
    }
    cout << (int)b.size();
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
