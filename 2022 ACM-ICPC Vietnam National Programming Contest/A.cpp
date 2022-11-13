#include <bits/stdc++.h>

using namespace std;

void open_file() {
#ifdef THEMIS
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif  // THEMIS
}

struct DSU {
    vector<int> p;
    int n;

    DSU(int _n = 0) {
        n = _n;
        p = vector<int>(n + 7, -1);
    }

    int find_root(int u) {
        return p[u] < 0 ? u : p[u] = find_root(p[u]);
    }

    int Union(int u, int v) {
        int x = find_root(u);
        int y = find_root(v);
        if (x == y) return 0;
        if (p[x] > p[y]) swap(x, y);
        p[x] += p[y];
        p[y] = x;
        return 1;
    }
};

struct Query {
    int id;
    int R, u, v;
    Query(int _id, int _R, int _u, int _v) {
        id = _id;
        R = _R;
        u = _u;
        v = _v;
    }
    bool operator<(const Query &other) {
        return R < other.R;
    }
};

void sol() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, int> > edge;
    vector<Query> q;
    vector<int> id_sn;
    id_sn.push_back(0);
    for (int i = 0; i < m; i++) {
        char t;
        cin >> t;
        if (t == 'A') {
            int u, v;
            cin >> u >> v;
            edge.push_back({u, v});
        }
        if (t == 'C') {
            id_sn.push_back(edge.size());
        }
        if (t == 'Q') {
            int s, u, v;
            cin >> s >> u >> v;
            q.push_back(Query(q.size(), id_sn[s], u, v));
        }
        if (t == '?') {
            int u, v;
            cin >> u >> v;
            q.push_back(Query(q.size(), edge.size(), u, v));
        }
    }

    DSU dsu(n);
    sort(q.begin(), q.end());
    vector<int> ans(q.size());
    int L = 0;
    for (Query a : q) {
        while (L < a.R) {
            dsu.Union(edge[L].first, edge[L].second);
            L++;
        }
        ans[a.id] = dsu.find_root(a.u) != dsu.find_root(a.v);
    }

    for (int i = 0; i < (int)ans.size(); i++) {
        if (ans[i])
            cout << 'N';
        else
            cout << 'Y';
    }
}
int main() {
    open_file();
    int t = 1;
    // cin >> t;
    while (t--) sol();
}
